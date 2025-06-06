#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX_STRING 128
#define TOTAL_FILE 55

pthread_mutex_t recapMutex;
char *lines[TOTAL_FILE];
int lineCount = 0;

int checkDirectory(char *dir);
void createDirectory(char *dir);
void createFile(char *filePath);
char *getFiles(char *dir);
void writeTotal(char *filePath);
void *routine(void *args);

char *filmDir = "/home/sandy/praktikum-2-task-1-data/film/";
char *horrorDir = "/home/sandy/praktikum-2-task-1-data/film/FilmHorror/";
char *animasiDir = "/home/sandy/praktikum-2-task-1-data/film/FilmAnimasi/";
char *dramaDir = "/home/sandy/praktikum-2-task-1-data/film/FilmDrama/";
char *recapDir = "/home/sandy/praktikum-2-task-1-data/film/recap.txt";
char *totalDir = "/home/sandy/praktikum-2-task-1-data/film/total.txt";

typedef struct {
    int start;
    int stop;
    int step;
    char *name;
} ThreadArgs;

int main() {
    pthread_mutex_init(&recapMutex, NULL);
    pthread_t trabowoThread, peddyThread;

    if (checkDirectory(filmDir)) {
        printf("File has not been downloaded");
        exit(1);
    }

    createDirectory(horrorDir);
    createDirectory(animasiDir);
    createDirectory(dramaDir);
    createFile(recapDir);
    createFile(totalDir);

    char *line = strtok(getFiles(filmDir), "\n");
    while(line != NULL) {
        lines[lineCount] = malloc(strlen(line) + 1);
        strcpy(lines[lineCount], line);
        lineCount++;
        line = strtok(NULL, "\n");
    }

    ThreadArgs trabowoArgs = {0, 25, 1, "Trabowo"};
    ThreadArgs peddyArgs = {lineCount - 1, 24, -1, "Peddy"};
    pthread_create(&trabowoThread, NULL, routine, &trabowoArgs);
    pthread_create(&peddyThread, NULL, routine, &peddyArgs);
    pthread_join(trabowoThread, NULL);
    pthread_join(peddyThread, NULL);

    writeTotal(totalDir);

    pthread_mutex_destroy(&recapMutex);
    return 0;
}

int checkDirectory(char *dir) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        char* argv[] = {"/bin/test", "-d", dir, NULL};
        execv(argv[0], argv);
        perror("execv failed");
        exit(1);
    } else {
        if (wait(&status) < 0) {
            perror("wait failed");
            exit(1);
        }
        return WIFEXITED(status) && WEXITSTATUS(status) == 0 ? 0 : 1;
    }
}

void execvWrapper(char *argv[]) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        execv(argv[0], argv);
        perror("execv failed");
        exit(1);
    } else {
        if (wait(&status) < 0) {
            perror("wait failed");
            exit(1);
        }
    }
}

void createDirectory(char *dir) {
    char *argv[] = {"/bin/mkdir", "-p", dir, NULL};
    execvWrapper(argv);
}

void createFile(char *filePath) {
    char *argv[] = {"/bin/touch", filePath, NULL};
    execvWrapper(argv);
}

void moveFile(char *source, char *destination) {
    char *argv[] = {"/bin/mv", source, destination, NULL};
    execvWrapper(argv);
}

char* getFiles(char *dir) {
    pid_t pid;
    int status;
    int fd[2];
    char *buffer = (char *) malloc(MAX_STRING*TOTAL_FILE);

    if(pipe(fd) < 0) {
        perror("pipe failed");
        exit(1);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        char *argv[] = {"/bin/ls", dir, NULL};
        execv(argv[0], argv);

        perror("execv failed");
        exit(1);
    } else {
        close(fd[1]);
        ssize_t bufsize;
        while ((bufsize = read(fd[0], buffer, MAX_STRING*TOTAL_FILE - 1)) > 0) {
            buffer[bufsize] = '\0';
        }
        close(fd[0]);

        if (wait(&status) < 0) {
            perror("wait failed");
            exit(1);
        }
    }
    return buffer;
}

void writeTotal(char *filePath) {
    int horrorCount = 0, animasiCount = 0, dramaCount = 0;
    for (int i = 0; i < lineCount; i++) {
        if (strstr(lines[i], "horror")) horrorCount++;
        else if (strstr(lines[i], "animasi")) animasiCount++;
        else if (strstr(lines[i], "drama")) dramaCount++;
    }

    char *mostGenre;
    int maxCount = horrorCount;
    mostGenre = "FilmHorror";

    if (animasiCount > maxCount) {
        maxCount = animasiCount;
        mostGenre = "FilmAnimasi";
    }
    if (dramaCount > maxCount) {
        maxCount = dramaCount;
        mostGenre = "FilmDrama";
    }

    FILE *fp = fopen(filePath, "a");
    if (fp == NULL) {
        perror("Failed to open total.txt");
        exit(1);
    }

    fprintf(fp, "Jumlah film horror: %d\n", horrorCount);
    fprintf(fp, "Jumlah film animasi: %d\n", animasiCount);
    fprintf(fp, "Jumlah film drama: %d\n", dramaCount);
    fprintf(fp, "Genre dengan jumlah film terbanyak: %s\n", mostGenre);

    fclose(fp);
}

void addRecap(char *worker, char *fileName, char *genreDir) {
    pthread_mutex_lock(&recapMutex);

    FILE *recapFile = fopen(recapDir, "a");
    if (recapFile == NULL) {
        perror("Failed to open recap.txt");
        pthread_mutex_unlock(&recapMutex);
        exit(1);
    }

    time_t now = time(NULL);
    struct tm *localTime = localtime(&now);
    char timeBuffer[20];
    strftime(timeBuffer, sizeof(timeBuffer), "%d-%m-%Y %H:%M:%S", localTime);

    fprintf(recapFile, "[%s] %s: %s telah dipindahkan ke %s\n", timeBuffer, worker, fileName, genreDir);
    fclose(recapFile);

    pthread_mutex_unlock(&recapMutex);
}

void *routine(void *args) {
    ThreadArgs *threadargs = (ThreadArgs*) args;
    int index = threadargs->start;

    while ((index >= threadargs->start && index < threadargs->stop) || (index <= threadargs->start && index > threadargs->stop)) {
        char *fileName = lines[index];
        char *genre, *genreDir, fileDir[MAX_STRING*2];
        snprintf(fileDir, MAX_STRING*2, "%s%s", filmDir, fileName);

        if (strstr(fileName, "horror")) {
            genre = "FilmHorror";
            genreDir = horrorDir;
        } else if (strstr(fileName, "animasi")) {
            genre = "FilmAnimasi";
            genreDir = animasiDir;
        } else if (strstr(fileName, "drama")) {
            genre = "FilmDrama";
            genreDir = dramaDir;
        } else {
            index += threadargs->step;
            continue;
        }

        moveFile(fileDir, genreDir);
        addRecap(threadargs->name, fileName, genre);
        index += threadargs->step;
    }
    return NULL;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX_STRING 256
#define MAX_ROW 5400

pthread_mutex_t logMutex;
char *downloadLink = "https://drive.google.com/uc?export=download&id=12GWsZbSH858h2HExP3x4DfWZB1jLdV-J";
char *downloadPath = "/home/sandy/praktikum-2-task-2-data/netflixData.zip";
char *downloadDir = "/home/sandy/praktikum-2-task-2-data/";
char *netflixDataPath = "/home/sandy/praktikum-2-task-2-data/netflixData.csv";
char *logDir = "/home/sandy/praktikum-2-task-2-data/log.txt";
char *judulDir = "/home/sandy/praktikum-2-task-2-data/judul/";
char *tahunDir = "/home/sandy/praktikum-2-task-2-data/tahun/";

void clearTerminal();
void createDirectory(char *dir);
void createFile(char *filePath);
void downloadFile(char *destination, char *source);
void unzipFile(char *source, char *destination);
void removeFiles(char *files);
void *sortByNameRoutine();
void *sortByYearRoutine();
void createReport();
void showMenu();

typedef struct {
    char title[MAX_STRING];
    char director[MAX_STRING];
    char country[MAX_STRING];
    char releaseYear[MAX_STRING];
} Film;

int main() {
    pthread_mutex_init(&logMutex, NULL);

    createDirectory(downloadDir);
    createDirectory(judulDir);
    createDirectory(tahunDir);
    createFile(logDir);
    showMenu();

    pthread_mutex_destroy(&logMutex);
    return 0;
}

void showMenu() {
    int choice;
    do {
        printf("\n======= Menu =======\n");
        printf("1. Download File\n");
        printf("2. Mengelompokkan Film\n");
        printf("3. Membuat Report\n");
        printf("4. Keluar\n");
        printf("Pilih opsi: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                clearTerminal();
                downloadFile(downloadPath, downloadLink);
                unzipFile(downloadPath, downloadDir);
                removeFiles(downloadPath);
                break;
            case 2: {
                clearTerminal();
                pthread_t threadAbjad, threadTahun;
                if (pthread_create(&threadAbjad, NULL, sortByNameRoutine, NULL) != 0) {
                    perror("Failed to create thread for sortByNameRoutine");
                    exit(1);
                }
                if (pthread_create(&threadTahun, NULL, sortByYearRoutine, NULL) != 0) {
                    perror("Failed to create thread for sortByYearRoutine");
                    exit(1);
                }
                pthread_join(threadAbjad, NULL);
                pthread_join(threadTahun, NULL);
                break;
            }
            case 3:
                createReport();
                break;
            case 4:
                clearTerminal();
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid. Coba lagi.\n");
        }
    } while (choice != 4);
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

void clearTerminal() {
    char *argv[] = {"/bin/clear", NULL};
    execvWrapper(argv);
}

void createDirectory(char *dir) {
    char *argv[] = {"/bin/mkdir", "-p", dir, NULL};
    execvWrapper(argv);
}

void createFile(char *filePath) {
    char *argv[] = {"/bin/touch", filePath, NULL};
    execvWrapper(argv);
}

void downloadFile(char *destination, char *source) {
    char *argv[] = {"/bin/curl", "-L", "-o", destination, source, NULL};
    execvWrapper(argv);
}

void unzipFile(char *source, char *destination) {
    char *argv[] = {"/bin/unzip", "-o", source, "-d", destination, NULL};
    execvWrapper(argv);
}

void removeFiles(char *files) {
    char *argv[] = {"/bin/rm", "-r", files, NULL};
    execvWrapper(argv);
}

void removeQuotes(char *str) {
    int i = 0, j = 0;
    while (str[i]) {
        if (str[i] != '"') str[j++] = str[i];
        i++;
    }
    str[j] = '\0';
}

void parseLine(char *line, char *tokens[]) {
    int inQuotes = 0;
    int tokenCount = 0;
    char *start = line;
    line[strcspn(line, "\n")] = 0;

    for (char *ptr = line; *ptr; ptr++) {
        if (*ptr == '"') {
            inQuotes = !inQuotes;
        } else if (*ptr == ',' && !inQuotes) {
            *ptr = '\0';
            tokens[tokenCount++] = start;
            start = ptr + 1;
        }
    }
    tokens[tokenCount++] = start;
    for (int i = 0; i < tokenCount; i++) removeQuotes(tokens[i]);
}


void addLog(char *fileName, char *title, char *type) {
    pthread_mutex_lock(&logMutex);

    FILE *fp = fopen(fileName, "a");
    if (fp == NULL) {
        perror("Failed to open log.txt");
        pthread_mutex_unlock(&logMutex);
        exit(1);
    }

    time_t now = time(NULL);
    struct tm *localTime = localtime(&now);
    char timeBuffer[20];
    strftime(timeBuffer, sizeof(timeBuffer), "%H:%M:%S", localTime);

    fprintf(fp, "[%s] Proses mengelompokkan berdasarkan %s: sedang mengelompokkan untuk film %s\n", timeBuffer, type, title);
    fclose(fp);

    pthread_mutex_unlock(&logMutex);
}

int compareByName(const void *a, const void *b) {
    Film *pa = (Film *)a;
    Film *pb = (Film *)b;
    return strcmp(pa->title, pb->title);
}

int compareByYear(const void *a, const void *b) {
    Film *pa = (Film *)a;
    Film *pb = (Film *)b;
    return strcmp(pa->releaseYear, pb->releaseYear);
}

void *sortByNameRoutine() {
    FILE* fp;
    Film* films = (Film *) malloc(sizeof(Film)*MAX_ROW);
    fp = fopen(netflixDataPath, "r");
    if (!fp) {
        perror("Cannot open file");
        exit(1);
    }  
    int count = 0;
    char line[MAX_STRING*8];
    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp)) {
        char *tokens[10];
        parseLine(line, tokens);
        if (strcmp(tokens[0], "")!=0) strncpy(films[count].title, tokens[0], MAX_STRING);
        else films[count].title[0] = '\0';
        if (strcmp(tokens[1], "")!=0) strncpy(films[count].director, tokens[1], MAX_STRING);
        else films[count].title[0] = '\0';
        if (strcmp(tokens[2], "")!=0) strncpy(films[count].country, tokens[2], MAX_STRING);
        else films[count].title[0] = '\0';
        if (strcmp(tokens[3], "")!=0) strncpy(films[count].releaseYear, tokens[3], MAX_STRING);
        else films[count].title[0] = '\0';
        count++;
    }

    fclose(fp);
    qsort(films, count, sizeof(Film), compareByName);
    for (int i = 0; i < count; i++) {
        printf("\033[1;0H(Thread Abdjad) Processing line %d of %d...", i + 1, count);
        fflush(stdout);
        addLog(logDir, films[i].title, "Abjad");
        
        char first[2];
        char file[MAX_STRING*2];
        first[0] = films[i].title[0];
        first[1] = '\0';

        if(!isalnum(first[0])) snprintf(file, MAX_STRING*2, "%s%s%s", judulDir, "#", ".txt");
        else snprintf(file, MAX_STRING*2, "%s%s%s", judulDir, first, ".txt");
        createFile(file);
        FILE *fp = fopen(file, "a");
            if (fp == NULL) {
            perror("Failed to open file");
            exit(1);
        }
        fprintf(fp, "%s - %s - %s\n", films[i].title, films[i].releaseYear, films[i].director);
        fclose(fp);
    }
    free(films);
    return NULL;
}

void *sortByYearRoutine() {
    FILE* fp;
    Film* films = (Film *) malloc(sizeof(Film)*MAX_ROW);
    fp = fopen(netflixDataPath, "r");
    if (!fp) {
        perror("Cannot open file");
        exit(1);
    }  
    int count = 0;
    char line[MAX_STRING*8];
    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp)) {
        char *tokens[10];
        parseLine(line, tokens);
        if (strcmp(tokens[0], "")!=0) strncpy(films[count].title, tokens[0], MAX_STRING);
        else films[count].title[0] = '\0';
        if (strcmp(tokens[1], "")!=0) strncpy(films[count].director, tokens[1], MAX_STRING);
        else films[count].title[0] = '\0';
        if (strcmp(tokens[2], "")!=0) strncpy(films[count].country, tokens[2], MAX_STRING);
        else films[count].title[0] = '\0';
        if (strcmp(tokens[3], "")!=0) strncpy(films[count].releaseYear, tokens[3], MAX_STRING);
        else films[count].title[0] = '\0';
        count++;
    }

    fclose(fp);
    qsort(films, count, sizeof(Film), compareByYear);
    for (int i = 0; i < count; i++) {
        printf("\033[2;0H(Thread Tahun) Processing line %d of %d...", i + 1, count);
        fflush(stdout);
        addLog(logDir, films[i].title, "Tahun");
        
        char year[MAX_STRING];
        snprintf(year, MAX_STRING, "%s", films[i].releaseYear);
        char file[MAX_STRING*2 + 6];

        snprintf(file, MAX_STRING*2 + 6, "%s%s%s", tahunDir, year, ".txt");
        createFile(file);
        FILE *fp = fopen(file, "a");
            if (fp == NULL) {
            perror("Failed to open file");
            exit(1);
        }
        fprintf(fp, "%s - %s - %s\n", films[i].title, films[i].releaseYear, films[i].director);
        fclose(fp);
    }
    free(films);
    return NULL;
}

void createReport() {
    FILE *fp = fopen(netflixDataPath, "r");
    char line[MAX_STRING * 8];
    fgets(line, sizeof(line), fp);

    typedef struct {
        char country[MAX_STRING];
        int before2000;
        int after2000;
    } CountryStats;

    CountryStats stats[MAX_ROW];
    int statsCount = 0;

    while (fgets(line, sizeof(line), fp)) {
        char *tokens[10];
        parseLine(line, tokens);

        char *country = tokens[2];
        int year = atoi(tokens[3]);

        int found = 0;
        for (int i = 0; i < statsCount; i++) {
            if (strcmp(stats[i].country, country) == 0) {
                if (year < 2000) stats[i].before2000++;
                else stats[i].after2000++;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(stats[statsCount].country, country);
            stats[statsCount].before2000 = (year < 2000) ? 1 : 0;
            stats[statsCount].after2000 = (year >= 2000) ? 1 : 0;
            statsCount++;
        }
    }
    fclose(fp);

    char fileName[MAX_STRING];
    char file[MAX_STRING*2];
    time_t now = time(NULL);
    struct tm *localTime = localtime(&now);
    strftime(fileName, sizeof(fileName), "report_%d%m%Y.txt", localTime);
    snprintf(file, MAX_STRING*2, "%s%s", downloadDir, fileName);
    createFile(file);

    FILE *fpReport = fopen(file, "a");
    for (int i = 0; i < statsCount; i++) {
        fprintf(fpReport, "Negara: %s\n", stats[i].country);
        fprintf(fpReport, "Film sebelum 2000: %d\n", stats[i].before2000);
        fprintf(fpReport, "Film setelah 2000: %d\n\n", stats[i].after2000);
    }

    fclose(fpReport);
}
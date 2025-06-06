#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX_STRING 128
#define TOTAL_FILE 50

char *filmDir = "/home/sandy/praktikum-2-task-1-data/film/";

int checkDirectory(char *dir);
char *getFiles(char *dir);

int main() {
    srand(time(NULL));

    if (checkDirectory(filmDir)) {
        printf("File has not been downloaded");
        exit(1);
    }

    char *line = strtok(getFiles(filmDir), "\n");
    int randint = rand() % TOTAL_FILE;
    for(int i = 0; i < randint; i++) line = strtok(NULL, "\n");
    printf("Film for Trabowo & Peddy: '%s'\n", line);

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

char *getFiles(char *dir) {
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
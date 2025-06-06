#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

char *downloadLink = "https://drive.google.com/uc?export=download&id=1nP5kjCi9ReDk5ILgnM7UCnrQwFH67Z9B";
char *filmZipPath = "/home/sandy/praktikum-2-task-1-data/film.zip";
char *downloadDir = "/home/sandy/praktikum-2-task-1-data/";

void createDirectory(char *dir);
void downloadFile(char *destination, char *source);
void unzipFile(char *destination, char *source);
void removeFiles(char *file);

int main() {
    createDirectory(downloadDir);
    downloadFile(filmZipPath, downloadLink);
    unzipFile(filmZipPath, downloadDir);
    removeFiles(filmZipPath);
    return 0;
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

void downloadFile(char *destination, char *source) {
    char *argv[] = {"/bin/curl", "-L", "-o", destination, source, NULL};
    execvWrapper(argv);
}

void unzipFile(char *destination, char *source) {
    char *argv[] = {"/bin/unzip", "-o", destination, "-d", source, NULL};
    execvWrapper(argv);
}

void removeFiles(char *file) {
    char *argv[] = {"/bin/rm", "-r", file, NULL};
    execvWrapper(argv);
}
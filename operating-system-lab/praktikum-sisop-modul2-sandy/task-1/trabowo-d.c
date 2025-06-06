#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

char *filmDir = "/home/sandy/praktikum-2-task-1-data/film/";
char *filmZipDir = "/home/sandy/praktikum-2-task-1-data/film/zipped_film.zip";
char *files[3] = {"FilmHorror", "FilmAnimasi", "FilmDrama"};

void zipFiles(char *destination, char *sources[]);
void removeFiles(char *files[]);

int main() {
    chdir(filmDir);
    zipFiles(filmZipDir, files);
    removeFiles(files);
    chdir("home");
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

void zipFiles(char *destination, char *sources[]) {
    char *argv[] = {"/bin/zip", "-r", destination, sources[0], sources[1], sources[2], NULL};
    execvWrapper(argv);
}

void removeFiles(char *files[]) {
    char *argv[] = {"/bin/rm", "-r", files[0], files[1], files[2], NULL};
    execvWrapper(argv);
}
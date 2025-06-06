#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX_STRING 256
#define SHM_PROGRAM_KEY "task4shm"
#define SHM_NUMBER_KEY 1234

typedef struct {
    char message[MAX_STRING];
    int count;
} Message;

char *parentDir = "/home/sandy/praktikum-2-task-4-data/";
char *logDir = "/home/sandy/praktikum-2-task-4-data/sistem.log";

void addLog(char *fileName ,char *message, int count);
void createDirectory(char *dir);
void createFile(char *filePath);

int main() {
    createDirectory(parentDir);
    createFile(logDir);
    
    Message msg;
    char input[MAX_STRING];
    int tokenCount = 0;

    printf("Masukkan pesan (format: pesan;jumlah): ");
    fgets(input, MAX_STRING, stdin);

    char *tokens[5];
    tokens[0] = strtok(input, ";");
    while (tokens[tokenCount] != NULL) {
        tokenCount++;
        tokens[tokenCount] = strtok(NULL, ";");
    }
    
    strcpy(msg.message, tokens[0]);
    msg.count = atoi(tokens[1]);

    key_t key = ftok(SHM_PROGRAM_KEY, SHM_NUMBER_KEY);
    int shmid = shmget(key, sizeof(Message), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }
    Message *msgToSend = (Message *) shmat(shmid, NULL, 0);
    if (msgToSend == (void *) -1) {
        perror("shmat");
        exit(1);
    }

    strcpy(msgToSend->message, msg.message);
    msgToSend->count = msg.count;
    addLog(logDir, msg.message, msg.count);

    if (shmdt(msgToSend) == -1) {
        perror("shmdt");
        exit(1);
    }
}

void addLog(char *fileName ,char *message, int count) {
    FILE *fp = fopen(fileName, "a");
    if (fp == NULL) {
        perror("Failed to open sistem.log");
        exit(1);
    }

    fprintf(fp, "Message from client: %s \nMessage count: %d\n", message, count);
    fclose(fp);
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
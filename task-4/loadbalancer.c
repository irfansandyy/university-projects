#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/types.h>
#define MAX_STRING 256
#define SHM_PROGRAM_KEY "task4shm"
#define SHM_NUMBER_KEY 1234
#define MSG_PROGRAM_KEY "task4msg"
#define MSG_NUMBER_KEY 4321
#define CONTROL_TYPE 500
#define NUM_WORKERS 3
// Kernel Parameter msg_max: 64
// echo 128 > /proc/sys/kernel/msg_max

char *logDir = "/home/sandy/praktikum-2-task-4-data/sistem.log";

typedef struct {
    char message[MAX_STRING];
    int count;
} Message;

typedef struct {
    long type;
    char message[MAX_STRING];
} ThreadMessage;

void addLog(char *fileName ,char *message, int count);

int main() {
    key_t shmKey = ftok(SHM_PROGRAM_KEY, SHM_NUMBER_KEY);
    int shmid = shmget(shmKey, sizeof(Message), 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }
    Message *data = (Message *) shmat(shmid, NULL, 0);
    if (data == (void *) -1) {
        perror("shmat");
        exit(1);
    }

    key_t msgKey = ftok(MSG_PROGRAM_KEY, MSG_NUMBER_KEY);
    int msgid = msgget(msgKey, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }
    
    ThreadMessage tmsg;
    tmsg.type = CONTROL_TYPE;
    snprintf(tmsg.message, sizeof(tmsg.message), "%d", NUM_WORKERS);
    if (msgsnd(msgid, &tmsg, sizeof(tmsg) - sizeof(long), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }
    for (int i = 0; i < data->count; i++) addLog(logDir, data->message, i);
    for (int i = 0; i < data->count; i++) {
        tmsg.type = (i % NUM_WORKERS) + 1;
        strcpy(tmsg.message, data->message);
        if (msgsnd(msgid, &tmsg, sizeof(tmsg) - sizeof(long), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }
    }

    if (shmdt(data) == -1) {
        perror("shmdt");
        exit(1);
    }
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }
}

void addLog(char *fileName ,char *message, int index) {
    FILE *fp = fopen(fileName, "a");
    if (fp == NULL) {
        perror("Failed to open sistem.log");
        exit(1);
    }

    fprintf(fp, "Received at lb: %s (#message %d)\n", message, index);
    fclose(fp);
}
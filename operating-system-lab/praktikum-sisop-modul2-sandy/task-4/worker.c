#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MAX_STRING 256
#define MSG_PROGRAM_KEY "task4msg"
#define MSG_NUMBER_KEY 4321
#define CONTROL_TYPE 500

char *logDir = "/home/sandy/praktikum-2-task-4-data/sistem.log";
pthread_mutex_t logMutex;

typedef struct {
    long type;
    char message[MAX_STRING];
} ThreadMessage;

typedef struct {
    int workerId;
    int msgid;
} Worker;

void addLog(char *fileName ,char *message);
void *workerRoutine(void *arg);

int main() {
    pthread_mutex_init(&logMutex, NULL);
    int workerCount = 0;

    key_t key = ftok(MSG_PROGRAM_KEY, MSG_NUMBER_KEY);
    int msgid = msgget(key, 0666);
    if (msgid == -1) {
        perror("msgget");
        pthread_exit(NULL);
    }

    ThreadMessage tmsg;
    if (msgrcv(msgid, &tmsg, sizeof(tmsg) - sizeof(long), CONTROL_TYPE, 0) == -1) {
        perror("msgrcv");
        exit(1);
    } else workerCount = atoi(tmsg.message);
    
    pthread_t threads[workerCount];
    for (int i = 0; i < workerCount; i++) {
        Worker *args = malloc(sizeof(Worker));
        args->workerId = i + 1;
        args->msgid = msgid;

        if (pthread_create(&threads[i], NULL, workerRoutine, args) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }

    for (int i = 0; i < workerCount; i++) pthread_join(threads[i], NULL);
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }
    return 0;
}

void addLog(char *fileName ,char *message) {
    pthread_mutex_lock(&logMutex);

    FILE *fp = fopen(fileName, "a");
    if (fp == NULL) {
        perror("Failed to open sistem.log");
        pthread_mutex_unlock(&logMutex);
        exit(1);
    }

    fprintf(fp, "%s\n", message);
    fclose(fp);

    pthread_mutex_unlock(&logMutex);
}

void *workerRoutine(void *arg) {
    Worker *wargs = (Worker *)arg;
    int id = wargs->workerId;
    int msgid = wargs->msgid;
    free(wargs);

    ThreadMessage tmsg;
    int count = 0;
    while (1) {
        if (msgrcv(msgid, &tmsg, sizeof(tmsg.message), id, IPC_NOWAIT) != -1) {
            char messageBuffer[MAX_STRING*2];
            sprintf(messageBuffer, "Worker%d: message received", id);
            addLog(logDir, messageBuffer);
            count++;
        } else break;
        usleep(2000);
    }

    char finalMessage[MAX_STRING];
    sprintf(finalMessage, "Worker %d: %d messages", id, count);
    addLog(logDir, finalMessage);

    pthread_exit(NULL);
}
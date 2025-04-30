#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#define PROGRAM_NAME "calcshm"
#define PROGRAM_KEY 1234

int main() {
    key_t key = ftok(PROGRAM_NAME, PROGRAM_KEY);
    int shmid = shmget(key, sizeof(int), 0666);
    int *data = (int*) shmat(shmid, NULL, 0);
    printf("Hasil tambahan: %d\n", *data);

    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
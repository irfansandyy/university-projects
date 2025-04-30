#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#define PROGRAM_NAME "calcshm"
#define PROGRAM_KEY 1234

int main() {
    int a, b;
    printf("Masukkan 2 angka: ");
    scanf("%d %d", &a, &b);
    
    key_t key = ftok(PROGRAM_NAME, PROGRAM_KEY);
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    int *data = (int*) shmat(shmid, NULL, 0);
    *data = a + b;
    shmdt(data);
    return 0;
}
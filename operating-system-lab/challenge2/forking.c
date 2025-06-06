#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;

    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    
    if (pid == 0) {
        printf("Child Process: %d\n", getpid());
    } else {
        printf("Parent Process: %d\n", getpid());
    }
    return 0;
}
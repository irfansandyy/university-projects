#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    pid = fork();
    if(pid < 0) {
        exit(1);
        
    }
    if(pid == 0) {
        char *argv[] = {"/bin/mkdir", "-p", "childprocess1", NULL};
        execv(argv[0], argv);
    }
    wait(NULL);

    pid = fork();
    if(pid < 0) {
        exit(1);
        
    }
    if(pid == 0) {
        char *argv[] = {"/bin/touch", "childprocess1/childprocess2.txt", NULL};
        execv(argv[0], argv);
    }
    wait(NULL);
    
    char *argv[] = {"/bin/cp", "childprocess1/childprocess2.txt", "parentprocess.txt", NULL};
    execv(argv[0], argv);
}
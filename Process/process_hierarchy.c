#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    int num;
    pid_t pid;

    srandom(getpid());
    for(num= 0; num<3; num++){
        pid=fork();
        printf("Soy el proceso de ID %D y mi padre tiene %d de PID. \n", getpid(), getppid());
        if(pid==0) break; // para que no tengan hijso los hijos.
    }
    if(pid==0) sleep(2);
    else
        for(num=0; num<3; num++)
            printf("Fin del proceso de PID %d,\n", wait(NULL));

    return 0;
}
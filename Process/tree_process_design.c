#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
int main(int argc, char *argv[]){

    int num;
    pid_t pid1, pid2, pid3;
    int status1, status2, status3;

    if((pid2=fork()) == 0){
        //printf("pid1: Soy el proceso de ID %D y mi padre tiene %d de PID. \n", getpid(), getppid());
        
            printf("pid2: Soy el proceso de ID %D y mi padre tiene %d de PID. \n", getpid(), getppid());
            pid3 = fork();
            if(pid3 == 0){
                printf("pid3: Soy el proceso de ID %D y mi padre tiene %d de PID \n", getpid(), getppid());   
            }
            /*
            if(pid2 == 0){
                break;
            }
            */
    /*    

    }else{
        pid1=fork();
        if(pid1 == 0){ 
            printf("pid1: Soy el proceso de ID %D y mi padre tiene %d de PID \n", getpid(), getppid());   
            pid2=fork();
        }
        else{
            waitpid(pid1, &status1, 0);
            waitpid(pid2, &status2, 0);
            waitpid(pid3, &status3, 0);
            
        }
    }
    return 0;
}
*/
/* este va
int main(int argc, char *argv[]){

    int num;
    pid_t pid2, pid3;

    srandom(getpid());
    for(int num2=0; num2<1; num2++){    // ramas del primer nivel
        printf("pid1: Soy el proceso de ID %D y mi padre tiene %d de PID. \n", getpid(), getppid());
        pid2=fork();  //profundidad del arbol
        if(pid2==0) {
            printf("pid2: Soy el proceso de ID %D y mi padre tiene %d de PID. \n", getpid(), getppid());
            pid3 = fork();
            if(pid3 == 0){
                printf("pid3: Soy el proceso de ID %D y mi padre tiene %d de PID \n", getpid(), getppid());
            }
            break;
        }
    }
   
    
    pid1=fork();
    if(pid1==0){    
        for(int num2=0; num2<1; num2++){    // ramas del primer nivel
            printf("for 1: Soy el proceso de ID %D y mi padre tiene %d de PID. \n", getpid(), getppid());
            pid2=fork();
            if(pid2 == 0){
                printf("for 2: Soy el proceso de ID %D y mi padre tiene %d de PID \n", getpid(), getppid());
                pid3=fork();
                if(pid3 == 0){
                    printf("for 3: Soy el proceso de ID %D y mi padre tiene %d de PID \n", getpid(), getppid());
                }
                break;
            }
            break;
        }
    }
    *       
        
    
    
    
    
        
            
        /*
        if(pid1==0) {
            pid2=fork();
            printf("for 2: Soy el proceso de ID %D y mi padre tiene %d de PID. \n", getpid(), getppid());
            if(pid2==0) {
                pid3 = fork();
                printf("if  1: Soy el proceso de ID %D y mi padre tiene %d de PID. \n", getpid(), getppid());
                break; // para que no tengan mas hijos. Estos son los nodos del ultimo nivel
            }
        }
    }
        */




int main(int argc, char *argv[]){

    int num;
    pid_t pid;

    srandom(getpid());
    for(num= 0; num<2; num++){  //profundidad del arbol
        for(int num2=0; num2<4; num2++){    // ramas del primer nivel
            pid=fork();
            printf("for 1: Soy el proceso de ID %D y mi padre tiene %d de PID. \n", getpid(), getppid());
            if(pid == 0){
                break;
            }
        }
        if(pid==0) {
            for(num= 0; num<2; num++){ // ramas del segundo nivel.
                pid=fork();
                printf("for 2: Soy el proceso de ID %D y mi padre tiene %d de PID. \n", getpid(), getppid());
                if(pid==0) {
                    pid = fork();
                    printf("if  1: Soy el proceso de ID %D y mi padre tiene %d de PID. \n", getpid(), getppid());
                    break; // para que no tengan mas hijos. Estos son los nodos del ultimo nivel
                }
            }
        }
        break;
    }
    if(pid==0) sleep(2);
    else
        for(num=0; num<1; num++)
            printf("Fin del proceso de PID %d,\n", wait(NULL));

    return 0;
}


/*
    srandom(getpid());
    for(num= 0; num<2; num++){
        pid=fork();
        printf("for 1: Soy el proceso de ID %D y mi padre tiene %d de PID. \n", getpid(), getppid());
        if(pid==0) {
            for(num= 0; num<2; num++){
                pid=fork();
                printf("for 2: Soy el proceso de ID %D y mi padre tiene %d de PID. \n", getpid(), getppid());
                if(pid==0) {
                    pid = fork();
                    printf("if  1: Soy el proceso de ID %D y mi padre tiene %d de PID. \n", getpid(), getppid());
                    // if(pid==0) {
                    //     pid = fork();
                    //     printf("Soy el proceso de ID %D y mi padre tiene %d de PID. \n", getpid(), getppid());
                    //     //break; // para que no tengan hijso los hijos.
                    // }
                    break;
                }
            }
        }
        break;
    }
    if(pid==0) sleep(2);
    else
        for(num=0; num<1; num++)
            printf("Fin del proceso de PID %d,\n", wait(NULL));

    return 0;
}



int main()
{
    int pid, pid1, pid2, pid3, pidd, piddd, pidddd;

    // variable pid will store the
    // value returned from fork() system call
    pid = fork();
    // If fork() returns zero then it
    // means it is child process.
    if (pid == 0)
    {

        // First child needs to be printed
        // later hence this process is made
        // to sleep for 3 seconds.
        sleep(3);

        // This is first child process
        // getpid() gives the process
        // id and getppid() gives the
        // parent id of that process.
        printf("Soy el hijo 1(%d) y mi padre es %d\n",getpid(), getppid());
        pidd = fork();
        if(pidd == 0){
            printf("Soy el hijo 1(%d) y mi padre es %d\n",getpid(), getppid());
            piddd = fork();
            if(piddd == 0){
                printf("Soy el hijo 1(%d) y mi padre es %d\n",getpid(), getppid());
            }
        }else{
            pidddd = fork();
            if(pidddd == 0){
                printf("child[3] --> pid = %d and ppid = %d\n",getpid(), getppid());
            }
        }
    }else{
        pid1 = fork();
        if (pid1 == 0)
        {
            sleep(2);
            printf("child[2] --> pid = %d and ppid = %d\n", getpid(), getppid());
            pid3 = fork();
            if(pid3){
                sleep(1);
                printf("child[3] --> pid = %d and ppid = %d\n", getpid(), getppid());
            }
        }else{
            pid2 = fork();
            if (pid2 == 0)
            {
                // This is third child which is
                // needed to be printed first.
                printf("child[3] --> pid = %d and ppid = %d\n",
                       getpid(), getppid());
            }
            // If value returned from fork()
            // in not zero and >0 that means
            // this is parent process.
            else{
                // This is asked to be printed at last
                // hence made to sleep for 3 seconds.
                sleep(3);
                printf("parent --> pid = %d\n", getpid());
            }
        }
    }
    return 0;
}
*/
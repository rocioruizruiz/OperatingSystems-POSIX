#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//cuadrado de los impares
int main(void){
    pid_t pid1, pid2;
    int status1, status2;
    int pares[10], impares[10];    
    if((pid1=fork()) == 0){
        for(int i=0; i<19; i=i+2){  
            pares[i/2] = i*i;
        }
    }else{
        if((pid2=fork())== 0){
            for(int i=1; i <=19; i=i+2){
                impares[i/2] = i*i;
            }
        }else{
            waitpid(pid1, &status1, 0);
            waitpid(pid2, &status2, 0);
            int complet[20]; 
            for(int i=0; i<=19; i++){
                if(i%2==0){
                    complet[i] = pares[i/2];
                }else{
                    complet[i] = impares[i/2];
                }
                printf("%d", complet[i]);
            }
        }
    }
    exit(0);
}
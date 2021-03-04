#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#define MAXLON 1000

pthread_t thread1, thmain;
pthread_attr_t attr;

void *cuenta(void *args){
    char* nombre = (char*)args; // leo el parametro del thread ("ejemplo")
    int pos, cont=0, leidos;
    char cadena[MAXLON];
    int fd;

    fd = open(nombre, O_RDONLY);
    while((leidos= read(fd, cadena, MAXLON)) != 0){
        for(pos=0; pos<leidos; pos++){
            if((cadena[pos] == 'a') || (cadena[pos] == 'A')){
                cont ++;
            }
        }
    }
    printf("Fichero %s: %d caracteres 'a' o 'A' encontrados\n", nombre, cont);
    close(fd);
    pthread_exit(NULL); // termino la función del hilo (IMPRESCINDIBLE)
}

int main(int argc, char *argv[]){
    
    if(argc != 2){
        printf("Indica el nombre del fichero.\n");
        exit(0);
    }

    thmain = pthread_self();
    pthread_attr_init(&attr);
    char* argumento = argv[1];
    pthread_create(&thread1, &attr, cuenta, (void *)argumento); // crea thread 1 y le pasa el parametro del nombre del fichero "ejemplo"
    pthread_join(thread1, NULL); //espera a que termine el thread1
    printf("Programa terminado.");
    

    exit(0);
}
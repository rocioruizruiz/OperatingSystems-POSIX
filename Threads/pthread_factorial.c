#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>


pthread_t thread1, thread2, thmain;
pthread_attr_t attr;

void *factorial(void *);

void *factorial(void *args){
    int* num = (int*)args; // leo el parametro del thread (num1/num2)
    int fact = 1;
    printf("factorial de: %d \n", *num);
    while(*num > 1) {
       fact = fact * (*num);
       *num = *num - 1;
    }
     
    printf("es : %d \n", fact);
    pthread_exit(NULL); // termino la función del hilo (IMPRESCINDIBLE)
}

int main(void){

    printf("Vamos a calcular el factorial de dos numero de manera concurrente\n");

    thmain = pthread_self();
    pthread_attr_init(&attr);

    int num1 = 3, num2 = 4;

    pthread_create(&thread1, &attr, factorial, (void *)&num1); // crea thread 1 y le pasa el parametro num1
    pthread_create(&thread2, &attr, factorial, (void *)&num2); // crea thread 2 y le pasa el parametro num2

    pthread_join(thread1, NULL); //espera a que termine el thread1
    pthread_join(thread2, NULL); //espera a que termine el thread2

    printf("Programa terminado.");
    

     exit(0);
}
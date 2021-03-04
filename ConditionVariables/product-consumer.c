#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 2
#define MAX_STOCK 10

int stock = 3;
pthread_mutex_t stock_mutex;
pthread_cond_t stock_threshold_cv;

void *produce(void *t){
    long my_id = (long)t;
    printf("Starting produce(): thread %ld\n", my_id);
    while(1){
        pthread_mutex_lock(&stock_mutex);
        if(stock >= MAX_STOCK) {
            printf("consume(): thread %ld stock= %d. Going into wait...\n", my_id,stock);
            pthread_cond_wait(&stock_threshold_cv, &stock_mutex);
            printf("consume(): thread %ld, Condition signal received. stock = %d\n", my_id,stock);
        }
        if(stock < MAX_STOCK){
 		stock++;
        pthread_cond_signal(&stock_threshold_cv);
        printf("produce(): thread %ld, stock = %d\n", my_id, stock);
        pthread_mutex_unlock(&stock_mutex);
        /* Do some work so threads can alternate on mutex lock */
        sleep(2);
        }
    }
    
    pthread_exit(NULL);
}

void *consume(void *t){
    
 	long my_id = (long)t;
 	printf("Starting consume(): thread %ld\n", my_id);
 	
    while(1){
        pthread_mutex_lock(&stock_mutex);
        if(stock <= 0) {
            printf("consume(): thread %ld stock= %d. Going into wait...\n", my_id,stock);
            pthread_cond_wait(&stock_threshold_cv, &stock_mutex);
            printf("consume(): thread %ld, Condition signal received. stock = %d\n", my_id,stock);
        }
        if(stock > 0){
            stock --;
            printf("consume(): thread %ld, stock = %d\n", my_id, stock);
            pthread_cond_signal(&stock_threshold_cv);
            pthread_mutex_unlock(&stock_mutex);
            sleep(1);
        }
    }
    pthread_exit(NULL);
    
}

int main(int argc, char *argv[]){
    long consumidor = 1, productor = 2;
    pthread_t threads[2];
    pthread_attr_t attr;
    printf("initial stock = %d.\n", stock);
    
    /* Initialize mutex and condition variable objects */   
    pthread_mutex_init(&stock_mutex, NULL);
 	pthread_cond_init (&stock_threshold_cv, NULL);
    
    /* For portability, explicitly create threads in a joinable state */ 
    pthread_attr_init(&attr);
 	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
 	pthread_create(&threads[0], &attr, consume, (void *)consumidor);
 	pthread_create(&threads[1], &attr, produce, (void *)productor);
    
    /* Wait for all threads to complete */
    for(int i=0; i< NUM_THREADS; i++){
        pthread_join(threads[i], NULL);
    }
    printf ("Main(): Waited and joined with %d threads. Final value of stock = %d. Done.\n", NUM_THREADS, stock);
    pthread_attr_destroy(&attr);
 	pthread_mutex_destroy(&stock_mutex);
 	pthread_cond_destroy(&stock_threshold_cv);
 	pthread_exit (NULL);
}
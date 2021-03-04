#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stddef.h>
#include <errno.h>
#include <stdint.h>
#include <dispatch/dispatch.h>


struct rk_sema {
    dispatch_semaphore_t    sem;
};




void rn_sem_init(struct rk_sema *s, uint32_t value)
{
    dispatch_semaphore_t *sem = &s->sem;
    *sem = dispatch_semaphore_create(value);
}

static inline void
rn_sem_wait(struct rk_sema *s)
{
    dispatch_semaphore_wait(s->sem, DISPATCH_TIME_NOW);
}

static inline void
rn_sem_post(struct rk_sema *s)
{
    dispatch_semaphore_signal(s->sem);
}
void print(int buf[]);

// Data structure API
int isEmpty(int buf[]);
int isFull(int buf[]);
int addbufroduct(int buf[], int product);
int consume(int buf[]);

// Threads behaviour
void *prod(void *arg);
void *consumer(void *arg);

// Global variables
int buf[8] = {0, 0, 0, 0, 0, 0, 0, 0};
struct rk_sema semaforo;


int main(int argc, char **argv){
    pthread_t thread1, thread2;
    time_t t;
    

    srandom(time(&t));
    printf("Valor inicial del array:\n");
    print(buf);

    rn_sem_init(&semaforo, 0);
    pthread_create(&thread1, NULL, prod, NULL);
    pthread_create(&thread2, NULL, consumer, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    printf("Fin");
    //rn_sem_destroy(&semaforo);

    return 0;
}

int isEmpty(int buf[]){
    for(int i = 0; i < 8; i++){
        if(buf[i] != 0){
            return -1; 
        }
    }
    return 0; 
}

int isFull(int buf[]){
    for(int i = 0; i < 8; i++){
        if(buf[i] == 0){
            return -1;
        }
    }
    return 0; 
}

void *prod(void *arg){
  for(int i = 0; i<12; i++){
    rn_sem_wait(&semaforo);
    if(isFull(buf) == -1){
        int data = addProduct(buf, i+1);
        printf("%d added to buffer\n", data);
        print(buf);
    }
    rn_sem_post(&semaforo);
    sleep(random()%3);
  }
  pthread_exit (NULL);
}
int addProduct(int buf[], int product){
    for(int i = 0; i<8; i++){
        if(buf[i] == 0){
            buf[i] = product;
            return product;
        }
    }
    return -1; 
}




int consume(int buf[]){
    for(int i = 7; i >= 0; i--){
        if(buf[i] != 0){
            int consume = buf[i];
            buf[i] = 0;
            return consume;
        }
    }
    return -1; // Error
}

void *consumer(void *arg){
  for(int i = 0; i<20; i++){
    rn_sem_wait(&semaforo);
    if(isEmpty(buf) == -1){
        int data = consume(buf);
        printf("%d removed from buffer\n", data);
        print(buf);
    }
    rn_sem_post(&semaforo);
    sleep(random()%3);
  }
  pthread_exit(NULL);
}

void print(int buf[]){
    for(int i = 0; i < 8; i++){
        printf("%d ", buf[i]);
    }
    printf("\n\n");
}
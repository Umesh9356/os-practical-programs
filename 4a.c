//4a.  
#include <stdio.h>               //printf() 
#include <pthread.h>             //pthread function 
#include <semaphore.h>           //sem_t, sem_wait, sem_post 
#include <unistd.h>              //sleep() 
#include <stdlib.h>              //rand() and srand() 
#define BUFFER_SIZE 5            // size of circular buffer 
int buffer[BUFFER_SIZE]; 
int in = 0, out = 0;             // buffer index positions 
sem_t empty;                     // counts empty slots 
sem_t full;                      // counts filled slots 
pthread_mutex_t mutex;           // mutex for critical section 
// Producer Thread Function 
void* producer(void* arg) 
{ 
    int item; 
    while(1)                         // for(int i=0;i<10;i++) 
    { 
        item = rand() % 100;         // produce random item 
        sem_wait(&empty);            // wait until at least 1 empty slot 
        pthread_mutex_lock(&mutex);  // lock buffer for exclusive access 
        buffer[in] = item;           // insert item 
        printf("Produced: %d\n", item); 
        in = (in + 1) % BUFFER_SIZE; // circular increment 1 2 
        pthread_mutex_unlock(&mutex); // unlock buffer 
        sem_post(&full);              // increase count of full slots 
        sleep(1);                      // simulate production delay 
    } 
    // return NULL; // exit thread- for loop termination 
} 
// Consumer Thread Function 
void* consumer(void* arg) 
{ 
    int item; 
    while(1)                          // for(int i=0;i<10;i++) 
    { 
        sem_wait(&full);             // wait until at least 1 full slot  1 
        pthread_mutex_lock(&mutex);  // lock buffer 
        item = buffer[out];          // remove item 
        printf("Consumed: %d\n", item); 
        out = (out + 1) % BUFFER_SIZE; // circular increment   1234567 
pthread_mutex_unlock(&mutex); // unlock buffer 
sem_post(&empty);             
// increase count of empty slots 
sleep(1);                     
} 
// simulate consumption delay 
// return NULL; // exit thread- for loop termination 
} 
int main() 
{ 
pthread_t prodThread, consThread; 
// initialize semaphores and mutex 
sem_init(&empty, 0, BUFFER_SIZE); // initially all slots empty 
sem_init(&full, 0, 0);           
 // initially no slot full 
pthread_mutex_init(&mutex, NULL); 
// create producer and consumer threads 
pthread_create(&prodThread, NULL, producer, NULL); 
pthread_create(&consThread, NULL, consumer, NULL); 
// join threads (not reached, infinite loop) 
pthread_join(prodThread, NULL); 
pthread_join(consThread, NULL); 
return 0; 
} 
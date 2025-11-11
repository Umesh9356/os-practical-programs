#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
#include <stdint.h> // Include for intptr_t 
// Shared variables 
int readcount = 0;       // Count of active readers 
int shared_data = 0;     // Shared data resource 
// Semaphores and mutex 
sem_t wsem;              // Semaphore to control writer access 
pthread_mutex_t mutex;    
void READUNIT(int reader_id) {  //0 
    printf("Reader %d is reading the data: %d\n", reader_id, shared_data); 
    sleep(1); } 
void WRITEUNIT(int writer_id) {  //1 
    shared_data++; // Modify the shared resource 0 -> 1, 2 , 3 
    printf("Writer %d has written data: %d\n", writer_id, shared_data); 
    sleep(1); // Simulate time taken to write 
} 
// Reader function 
void* reader(void* arg) { 
    int reader_id = (intptr_t)arg; // Use intptr_t for safe pointer casting 
    while (1) { 
        // Entry section //0 
        pthread_mutex_lock(&mutex); 
        readcount++; //1 
        if (readcount == 1) // First reader locks the writer 
            sem_wait(&wsem); 
        pthread_mutex_unlock(&mutex); 
        // Critical section: Reading 
        READUNIT(reader_id); 
        // Exit section 
        pthread_mutex_lock(&mutex); 
        readcount--; 
        if (readcount == 0) // Last reader unlocks the writer 
            sem_post(&wsem); 
        pthread_mutex_unlock(&mutex); 
  sleep(1); 
    } } 
// Writer function 
void* writer(void* arg) { 
    int writer_id = (intptr_t)arg; 
    while (1) { 
        // Entry section 
        sem_wait(&wsem); // Only one writer at a time 
        // Critical section: Writing 
        WRITEUNIT(writer_id); 
        // Exit section 
        sem_post(&wsem); // Release the writer lock 
        sleep(1); 
    } } 
int main() { 
    // Initialization 
    pthread_t rtid[5], wtid[2];  
    int reader_ids[5] = {1, 2, 3, 4, 5}; 
    int writer_ids[2] = {1, 2}; 
    // Initialize semaphore and mutex 
    sem_init(&wsem, 0, 1); 
    pthread_mutex_init(&mutex, NULL); 
    // Create reader threads 
    for (int i = 0; i < 5; i++) { 
        pthread_create(&rtid[i], NULL, reader, (void*)(intptr_t)reader_ids[i]); 
    } 
    // Create writer threads 
    for (int i = 0; i < 2; i++) { 
        pthread_create(&wtid[i], NULL, writer, (void*)(intptr_t)writer_ids[i]); 
    } 
    // Join threads (in a real scenario, we would join to avoid premature exit) 
    for (int i = 0; i < 5; i++) { 
        pthread_join(rtid[i], NULL); 
    } 
    for (int i = 0; i < 2; i++) { 
        pthread_join(wtid[i], NULL); 
    } 
    // Cleanup 
    pthread_mutex_destroy(&mutex); 
    sem_destroy(&wsem); 
    return 0; 
} 
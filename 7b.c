// Reader Program (read_from_shm.c) 
#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdlib.h> 
int main() { 
key_t key = ftok("shmfile", 65); 
int shmid = shmget(key, 1024, 0666 | IPC_CREAT); 
if (shmid == -1) { 
perror("Shared memory access failed"); 
exit(1); 
} 
char *shared_memory = (char*) shmat(shmid, (void*)0, 0); 
if ((void*)shared_memory == (void*)-1) { 
perror("Shared memory attach failed"); 
exit(1); 
} 
printf("Data read from shared memory: %s\n", shared_memory); 
if (shmdt(shared_memory) == -1) { 
perror("Shared memory detach failed"); 
exit(1); 
} 
if (shmctl(shmid, IPC_RMID, NULL) == -1) { 
perror("Shared memory removal failed"); 
exit(1); 
} 
return 0; 
} 






// Writer Program (write_to_shm.c) 
#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <string.h> 
#include <stdlib.h> 
int main() { 
key_t key = ftok("shmfile", 65); 
int shmid = shmget(key, 1024, 0666 | IPC_CREAT); 
if (shmid == -1) { 
perror("Shared memory creation failed"); 
exit(1); 
} 
char *shared_memory = (char*) shmat(shmid, (void*)0, 0); 
if ((void*)shared_memory == (void*)-1) { 
perror("Shared memory attach failed"); 
exit(1); 
} 
printf("Enter data to write into shared memory: "); 
fgets(shared_memory, 1024, stdin); // Read input and store it in shared memory 
if (shmdt(shared_memory) == -1) { 
perror("Shared memory detach failed"); 
exit(1); 
} 
printf("Data written to shared memory.\n"); 
return 0; 
} 
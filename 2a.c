#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#define SIZE 5 
void sort_array(int *arr, int size) { 
    int temp; 
    for (int i = 0; i < size - 1; i++) { 
        for (int j = i + 1; j < size; j++) { 
            if (arr[i] > arr[j]) { 
                temp = arr[i]; 
                arr[i] = arr[j]; 
                arr[j] = temp; 
            }}}} 
void print_array(int *arr, int size) { 
    for (int i = 0; i < size; i++) 
        printf("%d ", arr[i]); 
    printf("\n"); 
} 
int main() { 
    int arr[SIZE] = {5, 2, 9, 1, 5}; 
    pid_t pid; 
    int status; 
    printf("Unsorted array: "); 
    print_array(arr, SIZE); 
    pid = fork(); 
    if (pid < 0) { 
        perror("fork failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (pid == 0) { 
        // CHILD PROCESS 
        printf("\n--- CHILD PROCESS ---\n"); 
        printf("Child PID: %d, Parent PID: %d\n", getpid(), getppid()); 
        sort_array(arr, SIZE); 
        printf("Sorted array by child: "); 
        print_array(arr, SIZE); 
        printf("Child exiting now...\n"); 
        printf("Child becomes ZOMBIE until parent calls wait().\n"); 
        exit(EXIT_SUCCESS); 
    }  
else { 
        // PARENT PROCESS 
        printf("\n--- PARENT PROCESS ---\n"); 
        printf("Parent PID: %d, Child PID: %d\n", getpid(), pid); 
        printf("Parent sleeping for 10 seconds... (Child will finish and become Zombie)\n"); 
        printf("Check zombie using: ps -l | grep %d\n", pid); 
        sleep(10); 
  waitpid(pid, &status, 0); 
        printf("\nParent collected zombie (wait done)\n"); 
 // ORPHAN DEMO 
        pid_t pid2 = fork(); 
      if (pid2 == 0) { 
            printf("\n--- NEW CHILD PROCESS (Orphan Demo) ---\n"); 
            printf("Child PID: %d, Parent PID: %d\n", getpid(), getppid()); 
            printf("Sleeping 5 seconds so parent exits first...\n"); 
            sleep(5); 
            printf("Now my Parent PID changed to %d (init/systemd)\n", getppid()); 
            printf("I am now an ORPHAN process.\n"); 
            exit(0); 
        } else { 
            printf("\nParent exiting now... (Next child will become orphan)\n"); 
            exit(0); 
        } 
    } 
    return 0; 
} 
 
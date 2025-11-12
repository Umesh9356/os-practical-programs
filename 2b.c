 
/*2b.Implement the C program in which main program accepts an array.  
Main program uses the FORK system call to create a new process called a child 
process.  
Parent process sorts an array and passes the sorted array to child process through the 
command line arguments of EXECVE system call. 
The child process uses EXECVE system call to load new program which display array in 
reverse order.*/ 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
// Function to sort array in ascending order 
void sortArray(int arr[], int n) { 
    int temp; 
    for (int i = 0; i < n - 1; i++) { 
        for (int j = i + 1; j < n; j++) { 
            if (arr[i] > arr[j]) { 
                temp = arr[i]; 
                arr[i] = arr[j]; 
                arr[j] = temp; 
            }}}} 
int main() { 
    int n; 
    printf("Enter number of elements: "); 
    scanf("%d", &n); 
    int arr[n]; 
    printf("Enter %d elements:\n", n); 
    for (int i = 0; i < n; i++) { 
        scanf("%d", &arr[i]); 
    } 
    // Sort array before sending 
    sortArray(arr, n); 
    printf("\n[Main Program] Sorted array: "); 
    for (int i = 0; i < n; i++) { 
        printf("%d ", arr[i]); 
    } 
    printf("\n"); 
    pid_t pid = fork(); 
    if (pid < 0) { 
        perror("Fork failed"); 
        exit(1); 
    }  
    else if (pid == 0) { 
        // Child process executes new program using execve() 
        printf("\n[Child] Executing displayrev program using execve()...\n"); 
        // Prepare arguments 
        char *args[n + 2]; 
        args[0] = "./displayrev"; 
        for (int i = 0; i < n; i++) { 
            char *num = malloc(10); 
            printf(num, "%d", arr[i]); 
            args[i + 1] = num; 
        } 
        args[n + 1] = NULL; 
        execve("./displayrev", args, NULL); 
        perror("execve failed"); 
        exit(1); 
    }  
    else { 
        // Parent waits for child 
        wait(NULL); 
        printf("\n[Main Program] Child process finished.\n"); 
    } 
    return 0; 
} 


/*display rev Program */
#include <stdio.h> 
#include <stdlib.h> 
int main(int argc, char *argv[]) { 
    int n = argc - 1; 
    int arr[n]; 
    for (int i = 1; i < argc; i++) { 
        arr[i - 1] = atoi(argv[i]); 
    } 
    printf("\n[Display Program] Array in reverse order: "); 
    for (int i = n - 1; i >= 0; i--) { 
        printf("%d ", arr[i]); 
    } 
    printf("\n"); 
return 0; 
}
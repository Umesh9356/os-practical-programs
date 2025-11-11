//3a.   
#include <stdio.h> 
// Structure to represent a process 
struct process { 
    int pid;     // Process ID 
    int at;      // Arrival Time 
    int bt;      // Burst Time 
    int ct;      // Completion Time 
    int tat;     // Turnaround Time 
    int wt;      // Waiting Time 
    int rem_bt;  // Remaining Burst Time (used for preemption) 
}; 
int main() { 
    int n;                         // Number of processes 
    int completed = 0;             // Count of completed processes 
    int time = 0;                  // Current time 
    int min_bt, idx = -1;          // To find the process with shortest remaining time 
    struct process p[10];          // Array to store process information 
    float avgwt = 0, avgtat = 0;   // For average waiting and turnaround time 
    int is_completed[10] = {0};    // Flags to check if a process is completed 
   // ------------------------------- 
    // Step 1: Input process details 
    // ------------------------------- 
    printf("Enter number of processes: "); 
    scanf("%d", &n); 
for (int i = 0; i < n; i++) { 
        p[i].pid = i + 1; // Assign process ID (P1, P2, P3, ...) 
        printf("Enter Arrival Time for P%d: ", i + 1); 
        scanf("%d", &p[i].at); 
        printf("Enter Burst Time for P%d: ", i + 1); 
        scanf("%d", &p[i].bt); 
        // Initially, remaining burst time = total burst time 
        p[i].rem_bt = p[i].bt; 
    } 
    printf("\n--- Preemptive Shortest Job First (SRTF) Scheduling ---\n"); 
    // -------------------------------------------------- 
    // Step 2: Run until all processes are completed 
    // -------------------------------------------------- 
    while (completed != n) { 
        min_bt = 9999; // Large number to find minimum 
        idx = -1;      // Index of process to execute next 
 
        // Find process with minimum remaining burst time that has arrived 
        for (int i = 0; i < n; i++) { 
            if (p[i].at <= time && is_completed[i] == 0 && p[i].rem_bt < min_bt && p[i].rem_bt > 
0) { 
                min_bt = p[i].rem_bt; 
                idx = i; 
            }} 
// If a process is found to execute 
        if (idx != -1) { 
            p[idx].rem_bt--; // Execute the process for 1 unit of time 5 4 
            time++;          // Increment current time 4 5 
 // If process completes its execution 
            if (p[idx].rem_bt == 0) { 
                p[idx].ct = time;                      // Completion time 
                p[idx].tat = p[idx].ct - p[idx].at;    // Turnaround time = CT - AT 
                p[idx].wt = p[idx].tat - p[idx].bt;    // Waiting time = TAT - BT 
 // Add to totals for average calculations 
                avgwt += p[idx].wt; 
                avgtat += p[idx].tat; 
  is_completed[idx] = 1; // Mark process as completed 
                completed++;// Increment completed count 
            } }  
        else { 
            // If no process has arrived yet at current time 
            time++; 
        }} 
// -------------------------------------------- 
    // Step 3: Display results in table format 
    // -------------------------------------------- 
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n"); 
    for (int i = 0; i < n; i++) { 
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",  
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt); 
    }    // -------------------------------------------- 
    // Step 4: Print average waiting and turnaround 
    // -------------------------------------------- 
    printf("\nAverage Waiting Time: %.2f", avgwt / n); 
    printf("\nAverage Turnaround Time: %.2f\n", avgtat / n); 
return 0; 
} 
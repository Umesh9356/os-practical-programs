#include <stdio.h> 
//    Define structure to hold process details 
struct Process { 
    int pid;    // Process ID 
    int at;     // Arrival Time 
    int bt;     // Burst Time 
    int rt;     // Remaining Time 
    int ct;     // Completion Time 
    int tat;    // Turnaround Time 
    int wt;     // Waiting Time 
}; 
int main() { 
    int n, tq; 
    //   Step 1: Input number of processes 
    printf("Enter number of processes: "); 
    scanf("%d", &n);  //n=4 
  struct Process p[n]; 
    //   Step 2: Input Arrival Time and Burst Time for each process 
    for (int i = 0; i < n; i++) { 
        p[i].pid = i + 1; 
        printf("Enter Arrival Time and Burst Time for Process %d: ", p[i].pid); 
        scanf("%d %d", &p[i].at, &p[i].bt); 
        p[i].rt = p[i].bt;   // Initialize Remaining Time = Burst Time 
    } 
//   Step 3: Input Time Quantum 
    printf("Enter Time Quantum: "); 
    scanf("%d", &tq); 
    //   Initialize all helper variables 
    int completed = 0, time = 0; 
    int queue[100], front = 0, rear = 0; // Ready queue 
    int visited[n], is_completed[n]; 
    for (int i = 0; i < n; i++) { 
        visited[i] = 0;       // Marks if process has entered the ready queue 
        is_completed[i] = 0;  // Marks if process has finished execution 
    } 
    //   Step 4: Find first arriving process (to start CPU time) 
    int first = 0; 
    for (int i = 1; i < n; i++) { 
        if (p[i].at < p[first].at) 
            first = i; 
    } 
   time = p[first].at;              // Start time from earliest arrival 
    queue[rear++] = first;           // Add first process to queue 
    visited[first] = 1; 
    float total_tat = 0, total_wt = 0;   // For calculating averages later 
    //   Step 5: Execute processes until all are completed 
    while (completed != n) { 
        // If queue is empty → CPU is idle 
        if (front == rear) { 
            int next_arrival = -1, min_at = 9999; 
            // Find next process that will arrive 
            for (int i = 0; i < n; i++) { 
                if (!is_completed[i] && !visited[i] && p[i].at < min_at) { 
                    min_at = p[i].at;//0 
                    next_arrival = i; 
                }            } 
// Move time forward to next process arrival 
            if (next_arrival != -1) { 
                time = p[next_arrival].at; 
                queue[rear++] = next_arrival; 
                visited[next_arrival] = 1; 
            } 
            continue; 
        } 
        //   Dequeue process for execution 
        int idx = queue[front++]; 
        if (front == 100) front = 0;  // Handle queue circularly 
        //   Case 1: Process needs more than 1 quantum 
        if (p[idx].rt > tq) { //p1=4 tq=3 3-> 1 
            time += tq;//0+3 = 3 
            p[idx].rt -= tq;// 1 
        }  
        //   Case 2: Process finishes within this quantum   3 p1=3 
        else { 
            time += p[idx].rt;//3 
            p[idx].rt = 0;//0 
            p[idx].ct = time;                // Completion Time 
            p[idx].tat = p[idx].ct - p[idx].at; // Turnaround Time = CT - AT 
            p[idx].wt = p[idx].tat - p[idx].bt; // Waiting Time = TAT – BT 
total_tat += p[idx].tat; 
            total_wt += p[idx].wt; 
 
            is_completed[idx] = 1;  // Mark process as done 
            completed++; 
        } 
 //   Step 6: Add newly arrived processes to the ready queue 
        for (int j = 0; j < n; j++) { 
            if (p[j].at <= time && !visited[j] && !is_completed[j]) { 
                queue[rear++] = j; 
                if (rear == 100) rear = 0; 
                visited[j] = 1; 
            }     } 
//   Step 7: If current process still needs CPU time → re-enqueue it 
        if (p[idx].rt > 0) { 
            queue[rear++] = idx; 
            if (rear == 100) rear = 0; 
        }    } 
//   Step 8: Display final table and averages 
    printf("\n--------------------------------------------------------\n"); 
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n"); 
    printf("--------------------------------------------------------\n"); 
    for (int i = 0; i < n; i++) { 
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", 
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt); 
    } 
    printf("--------------------------------------------------------\n"); 
    printf("Average Turnaround Time: %.2f\n", total_tat / n);  
    printf("Average Waiting Time: %.2f\n", total_wt / n); 
    return 0; 
}
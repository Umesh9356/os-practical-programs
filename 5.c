#include <stdio.h>
#include <stdbool.h> // For using bool type

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int main() {
    int num_processes, num_resources;
    int available[MAX_RESOURCES];
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int need[MAX_PROCESSES][MAX_RESOURCES];
    bool finish[MAX_PROCESSES];
    int safe_sequence[MAX_PROCESSES];
    int work[MAX_RESOURCES];

    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    printf("Enter the number of resources: ");
    scanf("%d", &num_resources);

    printf("Enter the available resources (e.g., R1 R2 R3): ");
    for (int i = 0; i < num_resources; i++) {
        scanf("%d", &available[i]);
    }

    printf("Enter the allocation matrix (P x R): \n");
    for (int i = 0; i < num_processes; i++) {
        printf("For Process P%d: ", i);
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the maximum matrix (P x R): \n");
    for (int i = 0; i < num_processes; i++) {
        printf("For Process P%d: ", i);
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Calculate Need matrix
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Initialize work = available
    for (int i = 0; i < num_resources; i++) {
        work[i] = available[i];
    }

    // Mark all processes as unfinished
    for (int i = 0; i < num_processes; i++) {
        finish[i] = false;
    }

    int count = 0;
    int safe_seq_index = 0;

    while (count < num_processes) {
        bool found_process = false;

        for (int p = 0; p < num_processes; p++) {
            if (finish[p] == false) {
                bool can_execute = true;

                for (int r = 0; r < num_resources; r++) {
                    if (need[p][r] > work[r]) {
                        can_execute = false;
                        break;
                    }
                }

                if (can_execute) {
                    for (int r = 0; r < num_resources; r++) {
                        work[r] += allocation[p][r];
                    }
                    finish[p] = true;
                    safe_sequence[safe_seq_index++] = p;
                    count++;
                    found_process = true;
                }
            }
        }

        if (!found_process && count < num_processes) {
            printf("\nSystem is in an UNSAFE state. No safe sequence exists.\n");
            return 0;
        }
    }

    printf("\nSystem is in a SAFE state. Safe sequence: ");
    for (int i = 0; i < num_processes; i++) {
        printf("P%d", safe_sequence[i]);
        if (i < num_processes - 1) {
            printf(" -> ");
        }
    }
    printf("\n");
    return 0;
}

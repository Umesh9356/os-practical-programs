 
/*6. Implement the C program for Page Replacement Algorithms: FCFS, LRU, and Optimal 
for frame size as minimum three. */
#include <stdio.h> 
#include <stdbool.h> 
#include <limits.h> 
void printFrames(int frames[], int frame_size) { 
    for (int i = 0; i < frame_size; i++) { 
        if (frames[i] == -1) { 
            printf(" - "); 
        } else { 
            printf(" %d ", frames[i]); 
        } 
    } 
    printf("\n"); 
} 
void fcfs(int pages[], int n_pages, int frame_size) { 
    int frames[frame_size]; 
    for (int i = 0; i < frame_size; i++) { 
        frames[i] = -1; // Initialize frames as empty 
    } 
  int page_faults = 0; 
    int frame_index = 0; // Pointer to the oldest page 
  printf("\n--- FCFS Page Replacement ---\n"); 
    for (int i = 0; i < n_pages; i++) { 
        int current_page = pages[i]; 
        bool found = false; 
        for (int j = 0; j < frame_size; j++) { 
            if (frames[j] == current_page) { 
                found = true; 
                break; 
            }    } 
  if (!found) { 
            page_faults++; 
            frames[frame_index] = current_page; 
            frame_index = (frame_index + 1) % frame_size;  
        } 
        printf("Page %d: ", current_page); 
        printFrames(frames, frame_size); 
    } 
    printf("Total FCFS Page Faults: %d\n", page_faults); 
} 
void lru(int pages[], int n_pages, int frame_size) { 
    int frames[frame_size]; 
    int recency[frame_size]; // Stores the last access time (index in pages array) 
    for (int i = 0; i < frame_size; i++) { 
        frames[i] = -1; 
        recency[i] = -1; 
    } 
  int page_faults = 0; 
 printf("\n--- LRU Page Replacement ---\n"); 
    for (int i = 0; i < n_pages; i++) { 
        int current_page = pages[i]; 
        bool found = false; 
        int found_index = -1; 
        for (int j = 0; j < frame_size; j++) { 
            if (frames[j] == current_page) { 
                found = true; 
                found_index = j; 
                break; 
            }     } 
if (!found) { 
               page_faults++; 
            int lru_index = -1; 
            int min_recency = INT_MAX; 
            for (int j = 0; j < frame_size; j++) { 
                if (frames[j] == -1) { // Empty frame available 
                    lru_index = j; 
                    break; 
                } 
                if (recency[j] < min_recency) { 
                    min_recency = recency[j]; 
                    lru_index = j; 
                } 
            } 
            frames[lru_index] = current_page; 
            recency[lru_index] = i; // Update recency 
        } else { 
            recency[found_index] = i;        } 
        printf("Page %d: ", current_page); 
        printFrames(frames, frame_size); 
    } 
    printf("Total LRU Page Faults: %d\n", page_faults); 
} 
void optimal(int pages[], int n_pages, int frame_size) { 
    int frames[frame_size]; 
    for (int i = 0; i < frame_size; i++) { 
        frames[i] = -1; 
    } 
   int page_faults = 0; 
    printf("\n--- Optimal Page Replacement ---\n"); 
    for (int i = 0; i < n_pages; i++) { 
        int current_page = pages[i]; 
        bool found = false; 
        for (int j = 0; j < frame_size; j++) { 
            if (frames[j] == current_page) { 
                found = true; 
                break;   }   } 
   if (!found) { 
            page_faults++; 
            int replace_index = -1; 
            bool empty_frame_found = false; 
            for (int j = 0; j < frame_size; j++) { 
                if (frames[j] == -1) { 
                    replace_index = j; 
                    empty_frame_found = true; 
                    break; 
                }     } 
if (!empty_frame_found) { 
                int farthest_future_index = -1; 
                int max_future_use = -1; 
  for (int j = 0; j < frame_size; j++) { 
                    int next_use = INT_MAX; // Initialize with a large value 
                    for (int k = i + 1; k < n_pages; k++) { 
                        if (frames[j] == pages[k]) { 
                            next_use = k; 
                            break; 
                        }                    } 
                    if (next_use > max_future_use) { 
                        max_future_use = next_use; 
                        farthest_future_index = j; 
                    } } 
                replace_index = farthest_future_index; 
            } 
            frames[replace_index] = current_page; 
        } 
        printf("Page %d: ", current_page); 
        printFrames(frames, frame_size); 
    } 
    printf("Total Optimal Page Faults: %d\n", page_faults); 
} 
int main() { 
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1}; 
    int n_pages = sizeof(pages) / sizeof(pages[0]); 
    int frame_size = 3;  
    fcfs(pages, n_pages, frame_size); 
    lru(pages, n_pages, frame_size); 
    optimal(pages, n_pages, frame_size); 
    return 0; 
}
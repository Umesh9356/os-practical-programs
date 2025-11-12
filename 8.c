/*Practical no 8 Implement the C program for Disk Scheduling Algorithms: SSTF, SCAN, 
C-Look considering the initial head position moving away from the spindle. 
SSTF:- */
#include <stdio.h> 
#include <stdlib.h> 
#define MAX_REQUESTS 100 
void SSTF(int requests[], int num_requests, int initial_head) { 
int completed[MAX_REQUESTS] = {0}; 
int current_head = initial_head; 
int total_distance = 0;
printf("\n\n Seek Sequence: "); 
for (int i = 0; i < num_requests; i++) { 
int min_index = -1; 
int min_distance = 1000000; // Large number 
// Find the closest request 
for (int j = 0; j < num_requests; j++) { 
if (!completed[j]) { 
int distance = abs(requests[j] - current_head); 
if (distance < min_distance) { 
min_distance = distance; 
min_index = j; 
}}} 
if (min_index != -1) { 
total_distance += min_distance; 
current_head = requests[min_index]; 
completed[min_index] = 1; 
printf("%d ", current_head); 
}} 
printf("\n Total Number of Seek Operations = %d\n", total_distance); 
} 
int main() { 
int requests[MAX_REQUESTS]; 
int num_requests, initial_head; 
printf("\nEnter number of disk requests: "); 
scanf("%d", &num_requests); 
printf("Enter disk requests: "); 
for (int i = 0; i < num_requests; i++) { 
scanf("%d", &requests[i]); 
} 
printf("Enter initial head position: "); 
scanf("%d", &initial_head); 
SSTF(requests, num_requests, initial_head); 
return 0; 
}  





//SCAN.c 
#include <stdio.h> 
#include <stdlib.h> 
#define MAX_REQUESTS 100 
void SCAN(int requests[], int num_requests, int initial_head, int direction) { 
int total_distance = 0; 
int current_head = initial_head; 
// Sort the requests 
for (int i = 0; i < num_requests - 1; i++) { 
for (int j = i + 1; j < num_requests; j++) { 
if (requests[i] > requests[j]) { 
int temp = requests[i]; 
requests[i] = requests[j]; 
requests[j] = temp; 
}}} 
printf("\n\n Seek Sequence: "); 
if (direction == 0) { // Moving left 
// Service requests moving left 
for (int i = num_requests - 1; i >= 0; i--) { 
if (requests[i] <= current_head) { 
total_distance += abs(requests[i] - current_head); 
current_head = requests[i]; 
printf("%d ", current_head); 
} 
} 
total_distance += abs(current_head - 0); 
current_head = 0; 
printf("0 ");  
for (int i = 0; i < num_requests; i++) { 
if (requests[i] > 0) { 
total_distance += abs(requests[i] - current_head); 
current_head = requests[i]; 
printf("%d ", current_head); 
}}} else { // Moving right 
// Service requests moving right 
for (int i = 0; i < num_requests; i++) { 
if (requests[i] >= current_head) { 
total_distance += abs(requests[i] - current_head); 
current_head = requests[i]; 
printf("%d ", current_head); 
} 
} 
// Move to the end of the disk (disk size = 200) 
total_distance += abs(current_head - 200); 
current_head = 200; 
printf("200 "); // Move to the end 
// Then service all requests < disk size 
for (int i = num_requests - 1; i >= 0; i--) { 
if (requests[i] < current_head) { 
total_distance += abs(requests[i] - current_head); 
current_head = requests[i]; 
printf("%d ", current_head); 
} 
} 
} 
printf("\n Total number of seek operations = %d\n", total_distance); 
} 
int main() { 
int requests[MAX_REQUESTS]; 
int num_requests, initial_head, direction; 
printf("\nEnter number of disk requests: "); 
scanf("%d", &num_requests); 
printf("Enter disk requests: "); 
for (int i = 0; i < num_requests; i++) { 
scanf("%d", &requests[i]); 
} 
printf("Enter initial head position: "); 
scanf("%d", &initial_head); 
printf("Enter direction (0 for left, 1 for right): "); 
scanf("%d", &direction); 
SCAN(requests, num_requests, initial_head, direction); 
return 0; 
}




// c- look

#include <stdio.h>
#include <stdlib.h>
void c_look(int requests[], int num_requests, int head, int direction) {
int i, j;
// Sort the requests
for (i = 0; i < num_requests - 1; i++) {
for (j = i + 1; j < num_requests; j++) {
if (requests[i] > requests[j]) {
int temp = requests[i];
requests[i] = requests[j];
requests[j] = temp;
}
}
}
printf("\n\n Seek Sequence: ");
int total_seek_operations = 0;
int current_position = head;
// Move based on direction
if (direction == 1) { // Moving to the right
// Service requests greater than the current head position
for (i = 0; i < num_requests; i++) {
if (requests[i] >= current_position) {
total_seek_operations += abs(current_position - requests[i]);
current_position = requests[i];
printf("%d ", current_position);
}
}
// Jump to the smallest request (circular movement)
if (current_position != requests[0]) {
total_seek_operations += abs(current_position - requests[0]);
current_position = requests[0];
printf("%d ", current_position);
}
// Service the remaining smaller requests
for (i = 0; i < num_requests; i++) {
if (requests[i] < head) {
total_seek_operations += abs(current_position - requests[i]);
current_position = requests[i];
printf("%d ", current_position);
}
}
} else { // Moving to the left
// Service requests smaller than the current head position
for (i = num_requests - 1; i >= 0; i--) {
if (requests[i] <= current_position) {
total_seek_operations += abs(current_position - requests[i]);
current_position = requests[i];
printf("%d ", current_position);
}
}
// Jump to the largest request (circular movement)
if (current_position != requests[num_requests - 1]) {
total_seek_operations += abs(current_position -
requests[num_requests - 1]);
current_position = requests[num_requests - 1];
printf("%d ", current_position);
}
// Service the remaining larger requests
for (i = num_requests - 1; i >= 0; i--) {
if (requests[i] > head) {
total_seek_operations += abs(current_position - requests[i]);
current_position = requests[i];
printf("%d ", current_position);
}
}
}
printf("\n Total number of seek operations = %d\n",
total_seek_operations);
}
int main() {
int num_requests, head, direction;
printf("\nEnter the number of requests: ");
scanf("%d", &num_requests);
int *requests = (int *)malloc(num_requests * sizeof(int));
printf("Enter the disk requests: ");
for (int i = 0; i < num_requests; i++) {
scanf("%d", &requests[i]);
}
printf("Enter the initial head position: ");
scanf("%d", &head);
printf("Enter the direction (0 for left, 1 for right): ");
scanf("%d", &direction);
c_look(requests, num_requests, head, direction);
free(requests);
return 0;
}
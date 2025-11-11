 #include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <fcntl.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <string.h> 
#define FIFO1 "/tmp/fifo1" 
#define FIFO2 "/tmp/fifo2" 
void countDetails(const char* sentence, int* chars, int* words, int* lines) { 
int i = 0; 
*chars = *words = *lines = 0; 
while (sentence[i] != '\0') { 
(*chars)++; 
if (sentence[i] == ' ' || sentence[i] == '\n') { 
(*words)++;  } 
if (sentence[i] == '\n') { 
(*lines)++;  } 
i++;  } 
if (sentence[i-1] != ' ' && sentence[i-1] != '\n') { 
(*words)++;   } 
if (sentence[i-1] != '\n') { 
(*lines)++;   } } 
int main() { 
char buffer[1024]; 
int fd1, fd2; 
pid_t pid; 
mkfifo(FIFO1, 0666); // FIFO for Process 1 to write and Process 2 to read 
mkfifo(FIFO2, 0666); // FIFO for Process 2 to write and Process 1 to read 
pid = fork(); // Create a child process 
if (pid > 0) { 
printf("Process 1: Enter a sentence: "); 
fgets(buffer, sizeof(buffer), stdin); 
fd1 = open(FIFO1, O_WRONLY); 
write(fd1, buffer, strlen(buffer) + 1); 
close(fd1); 
fd2 = open(FIFO2, O_RDONLY); 
read(fd2, buffer, sizeof(buffer)); 
printf("Process 1: Result from Process 2 -\n%s\n", buffer); 
close(fd2); 
} else if (pid == 0) { 
int chars, words, lines; 
char result[256]; 
fd1 = open(FIFO1, O_RDONLY); 
read(fd1, buffer, sizeof(buffer)); 
close(fd1); 
countDetails(buffer, &chars, &words, &lines); 
FILE *file = fopen("output.txt", "w"); 
fprintf(file, "Characters: %d\nWords: %d\nLines: %d\n", chars, words, lines); 
fclose(file); 
fd2 = open(FIFO2, O_WRONLY); 
snprintf(result, sizeof(result), "Characters: %d\nWords: %d\nLines: %d", chars, words, 
lines); 
write(fd2, result, strlen(result) + 1); 
close(fd2); 
} 
unlink(FIFO1); 
unlink(FIFO2); 
return 0; 
} 
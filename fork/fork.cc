#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    pid_t pid = fork(); // Create a new process
    if (pid < 0) {
        // Fork failed
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        printf("Child process : (PID: %d) executing 'ls' command...\n", getpid());
        
        // Replace the child process image with the 'ls' command
        execlp("ls", "ls", "-l", NULL);
        
        // If execlp returns, it means there was an error
        perror("Child process  : execlp failed");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        printf("Parent process : (PID: %d) waiting for child process...\n", getpid());
        
        // Wait for the child process to finish
        wait(NULL);
        printf("Parent process : Child process finished.\n");
    }
    
    return 0;
}






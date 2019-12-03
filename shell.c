#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LINE_LEN 1024
#define MAX_COMMAND_LINE_ARGS 128

char prompt[] = "shell > ";
char delimiters[] = " \t\r\n";
char **environ;

int main() {
    // Stores the string typed into the command line.
    char command_line[MAX_COMMAND_LINE_LEN];

    // Stores the tokenized command line input.
    char *arguments[MAX_COMMAND_LINE_ARGS];

    while (true) {
        // Print the shell prompt.
        printf("%s", prompt);
        fflush(stdout);

        // Read input from stdin and store it in command_line. If there's an
        // error, exit immediately. (If you want to learn more about this line,
        // you can Google "man fgets")
        if ((fgets(command_line, MAX_COMMAND_LINE_LEN, stdin) == NULL) && ferror(stdin)) {
            fprintf(stderr, "fgets error");
            exit(0);
        }

        // If the user input was EOF (ctrl+d), exit the shell.
        if (feof(stdin)) {
            printf("\n");
            fflush(stdout);
            fflush(stderr);
            return 0;
        }

        // TODO:
        // 1. Tokenize the command line input (split it on whitespace)
        // 2. Create a child process which will execute the command line input
        // 3. The parent process should wait for the child to complete

        // Hints (put these into Google):
        // man fork
        // man execve
        // man wait
        // man strtok

        char *cmd;
        char *arg;
        int i = 0;
        cmd = strtok(command_line,delimiters);
        arg = strtok(NULL,delimiters);
        while (arg != NULL){
          arguments[i] = arg;
          i+=1;
          arg = strtok(NULL,delimiters);
        }

        pid = fork();

        if (pid < 0){
          perror("Fork error!\n");  // If fork() fails it does not create a child and returns -1.
          exit(1);
        } else if (pid == 0) {
          printf("This is the Child process!\n");
          if (execve(cmd, arguments, environ) < 0) {
            perror("Execution error!\n");   // Input is not executable.
            exit(1);
          }
          exit(0);
        } else {
          printf("This is the Parent process!\n");
          wait(NULL);
          printf("Child has terminated.\n");
        }
    }

    // This should never be reached.
    return -1;
}

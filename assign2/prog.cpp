/**
 * Assignment 2: Simple UNIX Shell
 * @file pcbtable.h
 * @author Nicholas Everekyan, Kevin Gallagher
 * @brief This is the main function of a simple UNIX Shell. You may add additional functions in this file for your implementation
 * @version 0.1
 */
// You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

#define MAX_LINE 80 // The maximum length command

char history[MAX_LINE]; // Declares history buffer to store the last command

/**
 * @brief parse out the command and arguments from the input command separated by spaces
 *
 * @param command
 * @param args
 * @return int
 */
int parse_command(char command[], char *args[]) 
{
    int num_args = 0;
    char *token;

    // Remove trailing newline character from the command if it exists
    if ((token = strchr(command, '\n')) != NULL) {
        *token = '\0';
    }

    // Use strtok to split the command into tokens (arguments)
    token = strtok(command, " ");
    while (token != NULL) {
        // Check if the token ends with '&'
        int len = strlen(token);
        if (token[len - 1] == '&') {
            token[len - 1] = '\0';  // Remove '&' from the token
            args[num_args++] = token;  // Save the command (without '&')
            break;  // '&' marks the end, no more tokens to process
        }
        args[num_args++] = token;  // Save the argument
        token = strtok(NULL, " "); // Continue tokenizing
    }

    args[num_args] = NULL;  // Null-terminate the argument array
    return num_args;        // Return the number of arguments parsed
}

// Function to execute a command in the child process
void execute_command(char *args[], int background) 
{
    pid_t pid = fork();

    if (pid == 0) {  // Child process
        if (execvp(args[0], args) == -1) {
            cout << "Command not found" << endl;
        }
        exit(EXIT_FAILURE);
    } else if (pid > 0) {  // Parent process
        if (!background) {
            wait(NULL);  // Wait for child to complete if not running in the background
        }
    } else {  // Fork failed
        perror("Fork failed");
    }
}

// Function to handle history (!!) command
// Added execution of command within this function as it was not executing within the main loop
void handle_history(char *args[])
{
    if (strlen(history) == 0) {
        cout << "No command history found." << endl;
    } else {
        cout << history << endl;
        strcpy(args[0], history);  // Set current command to the last history command
    }
}

// Function to handle pipe commands (cmd1 | cmd2)
void execute_pipe_command(char *args1[], char *args2[])
{
    int pipefd[2];  // File descriptors for pipe: pipefd[0] is read end, pipefd[1] is write end
    pid_t pid1, pid2;

    // Create the pipe
    if (pipe(pipefd) == -1) {
        perror("Pipe failed");
        return;
    }

    // First command (left side of pipe)
    pid1 = fork();
    if (pid1 == 0) {
        // Redirect stdout to the pipe's write end
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);  // Close unused read end
        close(pipefd[1]);  // Close write end after redirect

        if (execvp(args1[0], args1) == -1) {
            perror("Execution failed (cmd1)");
        }
        exit(EXIT_FAILURE);
    }

    // Second command (right side of pipe)
    pid2 = fork();
    if (pid2 == 0) {
        // Redirect stdin to the pipe's read end
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[1]);  // Close unused write end
        close(pipefd[0]);  // Close read end after redirect

        if (execvp(args2[0], args2) == -1) {
            perror("Execution failed (cmd2)");
        }
        exit(EXIT_FAILURE);
    }

    // Close pipe in the parent
    close(pipefd[0]);
    close(pipefd[1]);

    // Wait for both child processes to finish
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

// Function to check if there is a pipe in the command and split into two commands
bool find_pipe(char *args[], char *args1[], char *args2[])
{
    int i = 0, j = 0, pipe_index = -1;

    // Search for the pipe symbol in the arguments
    while (args[i] != NULL) {
        if (strcmp(args[i], "|") == 0) {
            pipe_index = i;
            break;
        }
        i++;
    }

    if (pipe_index == -1) {
        return false;  // No pipe found
    }

    // Split into two command arrays: args1 (before pipe) and args2 (after pipe)
    for (i = 0; i < pipe_index; i++) {
        args1[i] = args[i];
    }
    args1[pipe_index] = NULL;

    for (j = 0, i = pipe_index + 1; args[i] != NULL; i++, j++) {
        args2[j] = args[i];
    }
    args2[j] = NULL;

    return true;
}

// Function to execute commands with input and output redirection
void execute_command_redirection(char *args[], int background)
{
    int i = 0, input_redirect = 0, output_redirect = 0;
    char *input_file = NULL;
    char *output_file = NULL;

    while(args[i] != NULL){
        // Check for input file
        if(strcmp(args[i], "<") == 0){
            input_redirect = 1;
            // Set input file name
            input_file = args[i + 1];
            args[i] = NULL;
        } else if(strcmp(args[i], ">") == 0){
            // Same for output
            output_redirect = 1;
            output_file = args[i + 1];
            args[i] = NULL;
        }
        i++;
    }

    pid_t pid = fork();

    if(pid == 0){
        // Child process
        // Handle redirection
        if(input_redirect){
            int fd = open(input_file, O_RDONLY);
            if(fd == -1){
                perror("Failed to open input file");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }

        // Same for output
        if(output_redirect){
            int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if(fd == -1){
                perror("Failed to open output file");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }


        // Execute command
        if(execvp(args[0], args) == -1){
            cout << "Command not found" << endl;
            exit(EXIT_FAILURE);
        }
        else if(pid > 0 && !background){
            wait(NULL);
        }
    }    
}


/**
 * @brief The main function of a simple UNIX Shell. You may add additional functions in this file for your implementation
 * @param argc The number of arguments
 * @param argv The array of arguments
 * @return The exit status of the program
 */
int main(int argc, char *argv[])
{
    char command[MAX_LINE];       // The command that was entered
    char *args[MAX_LINE / 2 + 1]; // Hold parsed out command line arguments
    char *args1[MAX_LINE / 2 + 1]; // Command before pipe
    char *args2[MAX_LINE / 2 + 1]; // Command after pipe
    int should_run = 1;           /* flag to determine when to exit program */

    memset(history, 0, sizeof(history));  // Initialize history

    while (should_run)
    {
        printf("osh> ");
        fflush(stdout);

        // Read the input command
        if (fgets(command, MAX_LINE, stdin) == NULL) {
            perror("fgets failed");
            continue;
        }

        // Check for empty input
        if (command[0] == '\n' || command[0] == '\0' || command[0] == ' ') continue;

        // Check for history (!!)
        if (strcmp(command, "!!\n") == 0) {
            handle_history(args);
            continue;
        }

        // Save command to history if it's not !!
        strcpy(history, command);

        // Parse the input command
        int num_args = parse_command(command, args);

        // Check if the user wants to exit
        if (strcmp(args[0], "exit") == 0) {
            should_run = 0;
            continue;
        }

        // Check if the command should be run in the background
        int background = 0;
        if (strcmp(args[num_args - 1], "&") == 0) {
            background = 1;
            args[num_args - 1] = NULL;  // Remove '&' from arguments
        }

        // Check if there's a pipe command
        if (find_pipe(args, args1, args2)) {
            execute_pipe_command(args1, args2);
        } else {
            // Execute the parsed command
            execute_command_redirection(args, background);
        }
    }

    return 0;
}

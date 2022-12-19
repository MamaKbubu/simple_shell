#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_ARGS 64
#define MAX_COMMAND_LEN 1024
#define MAX_PATH_LEN 1024

int main(void)
{
    char command[MAX_COMMAND_LEN];
    char *args[MAX_ARGS];

    while (1) {
        printf("KaTshe>> ");
        fgets(command, MAX_COMMAND_LEN, stdin);

        int i;
	i = 0;

        args[i] = strtok(command, " \n");

        while (args[i] != NULL) {
            ++i;
            args[i] = strtok(NULL, " \n");
        }

        /* Check for exit */
        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        /* Check for cd */
        if (strcmp(args[0], "cd") == 0) {
            if (args[1] == NULL) {
                // No second argument, go to home
                char *home = getenv("HOME");
                int status = chdir(home);

                if (status != 0) {
                    printf("Error changing directory!\n");
                }
            } else {
                int status = chdir(args[1]);

                if (status != 0) {
                    printf("Error changing directory!\n");
                }
            }
        } else {
            // Find command
            char path[MAX_PATH_LEN];
            strcpy(path, "/bin/");
            strcat(path, args[0]);

            // Check if command exists
            if (access(path, X_OK) != -1) {
                int pid = fork();

                if (pid == 0) {
                    // Child process
                    execv(path, args);
                } else {
                    // Parent process
                    waitpid(pid, NULL, 0);
                }
            } else {
                // Command does not exist
                printf("Command not found!\n");
            }
        }
    }

    return 0;
}

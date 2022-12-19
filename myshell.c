#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_LEN 1000
#define MAX_ARGS 10

/* function declarations */
void parse_command(char *cmd_line, char **args);
int execute_command(char **args);

int main() {
    char cmd_line[MAX_LEN];
    char *args[MAX_ARGS];

    while (1) {
        printf(">> ");
        fgets(cmd_line, MAX_LEN, stdin);
        parse_command(cmd_line, args);
        if (execute_command(args) == -1)
            break;
    }

    return 0;
}

void parse_command(char *cmd_line, char **args) {
    int i = 0;
    args[i] = strtok(cmd_line, " \n");
    while (args[i] != NULL) {
        args[++i] = strtok(NULL, " \n");
    }
}

int execute_command(char **args) {
    int status;

    if (strcmp(args[0], "env") == 0) {
        /* display environment */
        char *env = getenv("PATH");
        printf("PATH=%s\n", env);
    } else if (strcmp(args[0], "exit") == 0) {
        /* exit shell */
        return -1;
    } else {
        /* execute command */
        pid_t pid = fork();
        if (pid < 0) {
            printf("Fork failed\n");
            return 1;
        } else if (pid == 0) {
            /* child process */
            if (execvp(args[0], args) < 0) {
                printf("Exec failed\n");
            }
            exit(0);
        } else {
            /* parent process */
            while (wait(&status) != pid);
        }
    }
    return 0;
}

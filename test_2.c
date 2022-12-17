#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


int main(void)
{
    char *full_command = NULL, *copy_command = NULL;
    size_t n = 0;
    ssize_t nchars_read; /* number of characters the user types */
    char *token;
    const char *delim = " \n";
    char **argv;
    int i = 0;
    int num_tokens = 0;

    /* print a prompt for the user to type something */
    printf("$ ");

    /* get the string that the user types in and pass it to full_command */
    nchars_read = getline(&full_command, &n, stdin);

    /* let's allocate space to store the characters read by getline */
    copy_command = malloc(sizeof(char) * nchars_read);

    if (copy_command == NULL){
        perror("tsh: memory allocation error");
        return (-1);
    }

    /* make a copy of the command that was typed */
    strcpy(copy_command, full_command);

    /* check if the getline function failed or reached EOF or user use CTRL + D */
    if (nchars_read == -1){
        printf("Exiting shell....\n");
        return (-1);
    }
    else {

        /* split the string (full_command) into an array of words */
        token = strtok(full_command, delim);

        /* allocate space to store the variable arguments but before then determine how many tokens are there*/
        while (token != NULL){
            num_tokens++;
            token = strtok(NULL, delim);
        }
        num_tokens++;

        /* use malloc to allocate enough space for 
	 * the pointer to the argument variables */
        argv = malloc(sizeof(char *) * num_tokens);

        token = strtok(copy_command, delim);

        for (i = 0; token != NULL; i++){
            argv[i] = malloc(sizeof(char) * strlen(token));
            strcpy(argv[i], token);
            token = strtok(NULL, delim);
        }
        argv[i] = NULL;

        /* execute the commands with execve */


        free(argv);
        free(full_command);
        free(copy_command);
    }

    return (0);
}

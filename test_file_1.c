#include "main.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	char *full_command = NULL, *copy_command = NULL;
	size_t n = 0;
	ssize_t nchars_read;
	char *token;
	const char *delim = " \n";
	char **argv;
	int i = 0;
	int num_tokens = 0;

	printf("KatTshe > ");

	/* get user string and pass it to full_command */
	nchars_read = getline(&full_command, &n, stdin);

	/* allocate space to store getline characters */
	copy_command = malloc(sizeof(char) * nchars_read);

	if (copy_command == NULL)
	{
		perror("Memory allocation Error");
		return (-1);
	}

	/*make copy of user typed command*/
	strcpy(copy_command, full_command);

	/* check state of getline function. Checks if */
	/* function failed or reached EOF or user use CTRL + D */
	if (nchars_read == -1)
	{
		printf("Exiting Shell\n");
		return (-1);
	}
	else
	{
		/* split string into array of words */
		token = strtok(full_command, delim);

		while (token != NULL)
		{
			num_tokens++;
			token = strtok(NULL, delim);
		}
		num_tokens++;

		/*allocate space for pointer to argv*/
		argv = malloc(sizeof(char *) * num_tokens);

		token = strtok(copy_command, delim);

		for (i = 0; token != NULL; i++)
		{
			argv[i] = malloc(sizeof(char) * strlen(token));
			strcpy(argv[i], token);
			token = strtok(NULL, delim);
		}
		argv[i] = NULL;

		free(argv);
		free(full_command);
		free(copy_command);
	}

	return (0);
}

#include "main.h"

/**
  *main - simple UNIX Command Intepreter
  * @argc: argument count
  * @argv: argument vector
  * Return: 0 on success
  */

int main(int argc, char **argv)
{
	char *prompt = "KatTshe > ";
	char *lineptr;
	size_t n = 0;
	ssize_t nchars_read;
	(void)argc; 
	/* (void)argv; */
	char *lineptr_copy = NULL;
	const char *delim = " \n";
	int num_tokens = 0;
	char *token;
	int i;

	while(1)
	{
		printf("%s", prompt);
		nchars_read = getline(&lineptr, &n, stdin);

		if (nchars_read == -1)
		{
			printf("Shell Exit\n");
			return (-1);
		}

		/* allocation of space for lineptr */
		lineptr_copy = malloc(sizeof(char) * nchars_read);
		if (lineptr_copy == NULL)
		{
			perror("Memory Allocation Error");
			return (-1);
		}

		/* copy lineptr to lineptr_copy */
		strcpy(lineptr_copy, lineptr);

		/* splits string into array */
		token = strtok(lineptr, delim);

		while (token != NULL)
		{
			num_tokens++;
			token = strtok(NULL, delim);
		}
		num_tokens++;

		/* allocate space for string array */
		argv = malloc(sizeof(char *) * num_tokens);

		/* store each token into argv array */
		token = strtok(lineptr, delim);

		for (i = 0; token != NULL; i++)
		{
			argv[i] = malloc(sizeof(char) * strlen(token));
			strcpy(argv[i], token);

			token = strtok(NULL, delim);
		}

		argv[i] = NULL;

		printf("%s", lineptr);

		/*free(lineptr);*/
	}
	
	free(lineptr);
	
	int main(void)
	{
		int id = fork();
		
		if (id == 0)
		{
			printf(" Child ID: %d, parent ID: %d \n",
				getpid(), getppid());
		}
		return (0);
	}
}

#include "main.h"

/**
  *main - simple UNIX Command Intepreter
  * @argc: argument count
  * @argv: argument vector
  * Return: 0 on success
  */

int main(int argc, char **argv)
{
	char *prompt = "KaTshe > ";
	char *lineptr = NULL, *lineptr_copy = NULL;
	size_t n = 0;
	ssize_t nchars_read;
	const char *delim = " \n";
	int num_tokens = 0;
	char *token;
	int i;
	(void)argc;

	while(1)
	{
		printf("%s", prompt);
		nchars_read = getline(&lineptr, &n, stdin);
		printf("nchars_read = %ld\n", nchars_read);

		if (nchars_read == -1)
		{
			printf("Shell Exit\n");
		//	return (-1);
		}
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

<<<<<<< HEAD
		/* splits string into array */
		token = strtok(lineptr, delim);
=======
	/* splits string into array */
	token = strtok(lineptr, delim);
>>>>>>> 325d78c67c2091385637f0d8449e24f8ebd24130

	while (token != NULL)
	{
		num_tokens++;
		token = strtok(NULL, delim);
	}
	num_tokens++;

	/* allocate space for string array */
	argv = malloc(sizeof(char *) * num_tokens);

	/* store each token into argv array */
	token = strtok(lineptr_copy, delim);

	for (i = 0; token != NULL; i++)
	{
		argv[i] = malloc(sizeof(char) * strlen(token));
		strcpy(argv[i], token);

		token = strtok(NULL, delim);
	}
	argv[i] = NULL;

	/* execute the command */
	execmd(argv); 

	
	free(lineptr);
<<<<<<< HEAD
	
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
=======
	free(lineptr_copy);

	return (0);
>>>>>>> 325d78c67c2091385637f0d8449e24f8ebd24130
}

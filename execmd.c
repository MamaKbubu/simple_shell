#include "main.h"
/**
  * execmd - 
  * @argv: argument vector
  * Return: 0 on success
  */

void execmd(char **argv)
{
	char *command = NULL;

	if (argv)
	{
		command = argv[0];
		
		if (execve(command, argv, NULL) == -1)
		{
			perror("Error");
		}
	}
}

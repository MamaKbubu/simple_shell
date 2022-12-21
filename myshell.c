#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <unistd.h> 

#define MAX_LEN 512

/** main - simple unix command line intepreter
  * @argc: command line argument count
  * @argv: Command line argument array
  * Return: 0 on SUCCESS
  */

int main(int argc, char *argv[]) 
{
	char command[MAX_LEN]; 
	int interactive = 0; 
	
	if (argc == 1) { 
		/* interactive mode */
		interactive = 1; 
		printf("Unix command interpreter \n"); 
		printf("Type 'quit' to exit \n"); 
	} 

	while (1) { 
		if (interactive) { 
			printf("$ "); 
			fgets(command, MAX_LEN, stdin); 
		} 
		else { 
			if (argc == 1) { 
				break; 
			} 
			strcpy(command, argv[1]); 
			for (int i = 2; i < argc; i++) { 
				strcat(command, " "); 
				strcat(command, argv[i]); 
			} 
		} 

		/* exit if user types 'quit' */
		if (strcmp(command, "exit\n") == 0) { 
			printf("Exiting...\n"); 
			break; 
		} 

		/* execute command using system()  */
		if (system(command) != 0) { 
			printf("Error executing command\n"); 
		} 
		if (!interactive) { 
			break; 
		} 
	} 

	return 0; 
}

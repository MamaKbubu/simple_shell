#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>

#define MAX_LINE 80
#define MAX_ARGS MAX_LINE(2 + 1)
int main(void)
{
	char *args[MAX_ARGS];
	char line[MAX_LINE];
	int should_run = 1;
<<<<<<< HEAD

	while(should_run) {
		printf("Kat_Tshego > ");
		fflush(stdout);

	/* read input*/
	fgets(line, MAX_LINE, stdin);

	/* tokenize input*/
	args[0] = strtok(line, " \n");
	int i = 0;

	while(args[i] != NULL) 
	{
		args[++i] = strtok(NULL, " \n");
        }


	pid_t pid = fork();
	if(pid == 0) {
		execvp(args[0], args);
		exit(1);
=======
	
	while (should_run)
	{
		printf("Kat_Tshego > ");
		fflush(stdout);
		// read input //
		fgets(gline, MAX_LINE, stdin);
		
		// tokenize input //
		args[0] = strtok(line, " \n")
		int i = 0;
		while (args[i] != NULL)
		{
			args[++i] = strtok(NULL, " \n");
        }
		// run command //
		pid_t pid = fork();
		
		if (pid == 0)
		{
			execvp(args[0], args);
			exit(1);
>>>>>>> 98e71d86f6207e80e43950574167e7045ea070ae
	}
    }
}

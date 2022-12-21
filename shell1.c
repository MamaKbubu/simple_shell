#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"

/*
 * Builtin function implementations.
*/

/**
 * @brief Builtin command: change directory.
 * @param args List of args.  args[0] is "cd".  args[1] is the directory.
 * @return Always returns 1, to continue executing.
 */
int lsh_cd(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "lsh: expected argument to \"cd\"\n");
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("lsh");
		}
	
}
  return 1;
}
/**
 * @brief Builtin command: print help.
 * @param args List of args.  Not examined
 * @return Always returns 1, to continue executing.
 */
int lsh_help(char **args)
{
	int i;
	(void)args;
	printf("Stephen Brennan's LSH\n");
	printf("Type program names and arguments, and hit enter.\n");
	printf("The following are built in:\n");
	
	for (i = 0; i < lsh_num_builtins(); i++) {
		printf("  %s\n", builtin_str[i]);
	}
	printf("Use the man command for information on other programs.\n");
	return 1;
}
/**
 * @brief Builtin command: exit.
 * @param args List of args.  Not examined.
 * @return Always returns 0, to terminate execution.
 */
int lsh_exit(char **args)
{
	(void)args;
	return 0;
}
/**
 * @brief Launch a program and wait for it to terminate.
 * @param args Null terminated list of arguments (including program).
 * @return Always returns 1, to continue execution.
 */
int lsh_launch(char **args)
{
	pid_t pid;
	int status;
	
	pid = fork();
	if (pid == 0) {
		/* Child process */
		if (execvp(args[0], args) == -1) {
			perror("lsh");
		}
		exit(EXIT_FAILURE);
	} else if (pid < 0) {
		/* Error forking */
		perror("lsh");
	} else {
		/* Parent process */
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return 1;
}
/**
   @brief Execute shell built-in or launch program.
   @param args Null terminated list of arguments.
   @return 1 if the shell should continue running, 0 if it should terminate
 */
int lsh_execute(char **args)
{
	int i;
	if (args[0] == NULL) {
		/* An empty command was entered. */
		return 1;
	}
	for (i = 0; i < lsh_num_builtins(); i++) {
		if (strcmp(args[0], builtin_str[i]) == 0) {
			return (*builtin_func[i])(args);
		}
	}
	return lsh_launch(args);
}
/**
 * @brief Read a line of input from stdin.
 * @return The line from stdin.
 */
char *lsh_read_line(void)
{
#ifdef LSH_USE_STD_GETLINE
	char *line = NULL;
	ssize_t bufsize = 0;
	/* have getline allocate a buffer for us */
	if (getline(&line, &bufsize, stdin) == -1) {
		if (feof(stdin)) {
			exit(EXIT_SUCCESS);  /* We received an EOF */
		} else {
			perror("lsh: getline\n");
			exit(EXIT_FAILURE);
		}
	}
  return line;
#else
#define LSH_RL_BUFSIZE 1024
  int bufsize = LSH_RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;
  
  if (!buffer) {
	  fprintf(stderr, "lsh: allocation error\n");
	  exit(EXIT_FAILURE);
}

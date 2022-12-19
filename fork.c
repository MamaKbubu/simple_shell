#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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

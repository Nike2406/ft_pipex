#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/errno.h>

int	main()
{
	int	id1 = fork();
	int	id2 = fork();
	if (id1 == 0)
		if (id2 == 0)
			printf("Were the process y\n");
		else
			printf("Were the process x\n");
	else
		if (id2 == 0)
			printf("Were the process z\n");
		else
			printf("Were the parent process!\n");
	while(wait(NULL) != -1 || errno != ECHILD)
	{
		printf("Waited for a child to finished\n");
	}
	return (0);
}
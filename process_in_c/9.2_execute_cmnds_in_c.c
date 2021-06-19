#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int	main()
{
	int pid = fork();
	if (pid < 0)
		return 1;
	if (pid == 0)
	{
		// Child process
		execlp("ping", "ping", "-c", "3", "ya.ru", NULL);
		// exec удаляет все последующие команды в процессе
		printf("You can't see this in terminal\n");
	}
	else
	{
		// Parent process
		wait(NULL);
		// printf("Some post process\n");
		printf("Success\n");
	}
	return (0);
}
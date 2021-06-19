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
		int err = execlp("ping", "ping", "-c", "3", "ya.ru", NULL);
		if (err < 0)
		{
			printf("Could not find program to execute!\n");
			return 2;
		}
		printf("You can't see this in terminal\n");
	}
	else
	{
		int wstatus;
		wait(&wstatus);
		if (WIFEXITED(wstatus))
		{
			int statusCode = WEXITSTATUS(wstatus);
			if (statusCode == 0)
				printf("Success\n");
			else
				printf("Failure with status code: %d\n", statusCode);
		}
	}
	return (0);
}
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

/*
	child process
	fd		file
	0		STDIN
	1		STDOUT
	2		STDERR
	3		pingRsults.txt
	4		pingRsults.txt
*/

int	main()
{
	int pid = fork();
	if (pid < 0)
		return 1;
	if (pid == 0)
	{
		int file = open("pinfResults.txt", O_WRONLY | O_CREAT, 0777);
		if (file < 0)
		{
			printf("Error of OPEN\n");
			return 3;
		}
		printf("The fd to pingResults: %d\n", file);
		// dup - клонирует процесс и присаивает ему новый fd
		// dup2 - клонирует процесс и присаивает fd вручную вторым параметром
		int file2 = dup2(file, STDOUT_FILENO);
		printf("The duplicated fd: %d\n", file2);
		close(file);
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int	main()
{
	int fd[2];
	if (pipe(fd) < 0)
		return 1;
	int pid1 = fork();
	if (pid1 < 0)
		return 2;
	if (pid1 == 0)
	{
		// Child process 1 (ping)
		execlp("ping", "ping", "-c", "5", "ya.ru", NULL);
	}
	waitpid(pid1, NULL, 0);

	return (0);
}

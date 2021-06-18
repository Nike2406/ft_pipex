#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int	main()
{
	/*
		1 - путь к исполняемому файлу
		2 - Параметр 1
		3 - Параметр 2
		4 - в конце всегда стоит NULL
	*/
	execl("/bin/ping", "/bin/ping", "-c", "3", "ya.ru", NULL);

	execlp("ping", "ping", "-c", "3", "ya.ru", NULL);

	char	*arr = {
		"ping",
		"ya.ru",
		NULL
	};
	char* env[] = {
		"TEST=environment variable",
		NULL
	};
	int	err = errno;
	execvpe("ping", arr, env);
	/*
		exec:
			l - list of parameters (execl);
			p - path of command (execlp);
			v - vector, array needs;
			e - environment;
	*/
	printf("Ping finished executing\n");
	return (0);
}
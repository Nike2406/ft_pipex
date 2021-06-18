#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int	main()
{
	execlp("ping", "ping", "-c", "3", "ya.ru", NULL);
	return (0);
}
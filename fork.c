#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int	main()
{
	int id = fork();
	printf("Hello world from: %d\n", id);
	return (0);
}
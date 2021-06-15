#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int	main()
{
	/*
	 fork() - создает дочернюю копию процесса
	 Выводтся попарно
	*/
	int	id = fork();

	/*
	Для вывода нечетных записей,
	можно использовать момент, что дочерний
	элемент всегда будет возвращать "0"
	*/
	if (id != 0)
		fork();

	printf("Hi!");
	return (0);
}
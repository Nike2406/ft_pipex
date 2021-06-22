#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

int	main()
{
	/*
		2 процесса:
		1 - Дочерний процесс генерирует случайные числа и
			отправлет их родителю
		2 - Родительский процесс суммирует все числа и
			выводит результат
	*/

	int	fd[2];
	if (pipe(fd) < 0)
		return (2);
	int pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
	{
		// Child
		close(fd[0]);
		int	n, i;
		int	arr[10];
		srand(time(NULL));
		n = rand() % 10 + 1;
		printf("Generated: ");
		for (i = 0; i < n; i++)
		{
			arr[i] = rand() % 11;
			printf("%d ", arr[i]);
		}
		printf("\n");
		// В первую очередь передается количество
		// элементов массива
		if (write(fd[1], &n, sizeof(int)) < 0)
			return (4);
		printf("Sent n = %d\n", n);
		if (write(fd[1], arr, sizeof(int) * n) < 0)
			return (3);
		printf("Sent array\n");
		close(fd[1]);
	}
	else
	{
		// Parent
		close(fd[1]);
		int	arr[10];
		int	n, i, sum = 0;
		if (read(fd[0], &n, sizeof(int)) < 0)
			return (5);
		printf("Received n = %d\n", n);
		if (read(fd[0], arr, sizeof(int) * n) < 0)
			return (6);
		printf("Received array\n");
		close(fd[0]);
		for (i = 0; i < n; i++)
			sum += arr[i];
		printf("Result is: %d\n", sum);
		wait(NULL);
	}

	return (0);
}

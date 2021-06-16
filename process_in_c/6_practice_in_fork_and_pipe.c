#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int	main()
{
	int	arr[] = {1, 2, 3, 4, 1, 2};
	int arrSize = sizeof(arr) / sizeof(int);
	int	fd[2];
	int start, end;
	if (pipe(fd) == -1)
		return 1;
	int id = fork();
	int	id1;
	if (id != 0)
		id1 = fork();
	if (id == -1 || id1 == -1)
		return 2;
	if (id == 0)
	{
		start = 0;
		end = arrSize / 2;
	}
	else if (id1 == 0)
	{
		start = arrSize / 2;
		end = arrSize;
	}
	int	sum = 0;
	int	i;
	if (id == 0 || id1 == 0)
	{
		for (i = start; i < end; i++)
		sum += arr[i];
		close(fd[0]);
		if (write(fd[1], &sum, sizeof(sum)) < 0)
			return 3;
		printf("Calculated partial sum: %d\n", sum);
		close(fd[1]);
	}
	else
	{
		int	sumFromChild1;
		int	sumFromChild2;
		close(fd[1]);
		if (read(fd[0], &sumFromChild1, sizeof(sumFromChild1)) < 0)
			return 4;
		if (read(fd[0], &sumFromChild2, sizeof(sumFromChild2)) < 0)
			return 5;
		close(fd[0]);
		int	totalSum = sumFromChild1 + sumFromChild2;
		printf("Total sum is %d\n", totalSum);
		wait(NULL);
	}
	return (0);
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <fcntl.h>

int	main()
{
	int	arr[5];
	int	fd = open("sum", O_RDONLY);
	if (fd < 0)
		return 1;
	int i;
	for (i = 0; i < 5; i++)
	{
		if (read(fd, &arr[i], sizeof(int)) < 0)
			return 2;
		printf("Recieved %d\n", arr[i]);
	}
	close(fd);
	return (0);
}
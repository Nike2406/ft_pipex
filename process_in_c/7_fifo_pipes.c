#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <fcntl.h>

int	main()
{
	if (mkfifo("myfifo1", 0777) < 0)
	{
		if (errno != EEXIST)
		{
			printf("Couldn't create fifo file\n");
			return 1;
		}
	}
	int	fd = open("myfifo1", O_WRONLY);
	int x = 97;
	if (write(fd, &x, sizeof(x)) < 0)
		return 2;
	close(fd);
	return (0);
}
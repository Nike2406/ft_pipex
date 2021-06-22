
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>

int	main()
{
	int	pid = fork();
	if(pid < 0)
		return (1);
	if (pid == 0)
	{
		while (1)
		{
			printf("Some output\n");
			usleep(50000);
		}
	}
	else
	{
		kill(pid, SIGSTOP);
		int t;

		do {
			printf("Time in seconds for execution: ");
			scanf("%d", &t);

			if (t > 0)
			{
				kill(pid, SIGCONT);
				sleep(t);
				kill(pid, SIGKILL);
			}
		} while (t > 0);
	}

	return (0);
};
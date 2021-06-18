#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int	main(int	argc, char **argv)
{
	/*
		Печать PID текущего процесса и PID процессапредка
	*/
	printf("PID = %d; PPID = %d\n\n", getpid(), getppid());
	/*
		создание нового процесса, с этого момента два
		процесса функционируют параллельно и независимо
	*/
	fork();
	/*
		оба процесса печатают PID текущего процесса и PID
		процесса-предка
	*/
	printf("PID = %d; PPID = %d\n", getpid(), getppid());

	return (0);
}

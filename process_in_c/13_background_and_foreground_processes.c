#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

void	handle_sigtstp(int sig)
{
	printf("Stom not allowed\n");
}

int	main()
{
	struct sigaction sa;
	sa.sa_handler = &handle_sigtstp;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGTSTP, &sa, NULL);

	int	x;
	/*
		В системе Linux работает остановка
		запущенного процесса (не путать с прекращением)
		компбинацией cntrl + Z, которую можно продолжить
		командой fg (foreground)
	*/

	printf("Input number: ");
	scanf("%d", &x);
	printf("Result %d * 5 = %d\n", x, x * 5);

	return (0);
}

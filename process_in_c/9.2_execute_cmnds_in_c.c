#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int	main()
{
	int pid = fork();
	if (pid < 0)
		return 1;
	if (pid == 0)
	{
		// Child process
		// exec возвращает номер результата выполнения
		int err = execlp("ping", "ping", "-c", "3", "ya.ru", NULL);
		if (err < 0)
		{
			printf("Could not find program to execute!\n");
			return 2;
		}
		// exec удаляет все последующие команды в процессе
		printf("You can't see this in terminal\n");
	}
	else
	{
		// Parent process
		// wait ожидает выполнения потомка, а только после
		// выполняет свои комманды
		int wstatus;
		// Проверка успешного завершения программы
		wait(&wstatus);
		/*
			Если status не равен NULL, то функции wait и waitpid
			сохраняют информацию о статусе в переменной, на которую
			указывает status. Этот статус можно проверить с помощью
			нижеследующих макросов (они принимают в качестве аргумента
			буфер (типа int), --- а не указатель на буфер!):

			WIFEXITED(status)
				не равно нулю, если дочерний процесс успешно завершился.
			WEXITSTATUS(status)
				возвращает восемь младших битов значения,
				которое вернул завершившийся дочерний процесс.
				Эти биты могли быть установлены в аргументе функции
				exit() или в аргументе оператора return функции main().
				Этот макрос можно использовать, только если WIFEXITED
				вернул ненулевое значение.
			WIFSIGNALED(status)
				возвращает истинное значение, если дочерний процесс
				завершился из-за необработанного сигнала.
			WTERMSIG(status)
				возвращает номер сигнала, который привел к завершению
				дочернего процесса. Этот макрос можно использовать,
				только если WIFSIGNALED вернул ненулевое значение.
			WIFSTOPPED(status)
				возвращает истинное значение, если дочерний процесс,
				из-за которого функция вернула управление, в настоящий
				момент остановлен; это возможно, только если использовался
				флаг WUNTRACED или когда подпроцесс отслеживается (см. ptrace(2)).
			WSTOPSIG(status)
				возвращает номер сигнала, из-за которого дочерний процесс
				был остановлен. Этот макрос можно использовать, только если
				WIFSTOPPED вернул ненулевое значение.
		*/
		if (WIFEXITED(wstatus))
		{
			int statusCode = WEXITSTATUS(wstatus);
			if (statusCode == 0)
				printf("Success\n");
			else
				printf("Failure with status code: %d\n", statusCode);
		}
	}
	return (0);
}
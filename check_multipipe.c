typedef struct s_descriptors
{
	int	fd[2];
}				t_descriptors;

t_descriptors *create_descriptors(int count) //Создать динамич массив из файловых дескрипторов
{
	t_descriptors *descriptors;
	descriptors = malloc(sizeof(t_descriptors) * count);
	if (!descriptors)
		def_err("error: fatal\n", 1);
	return (descriptors);
}

void	child_body(t_descriptors *descriptors, int pos, int blocks)
{
	int	ret;
	dup2(descriptors[pos].fd[0], STDIN_FILENO);
	if (pos < blocks - 1) //Если НЕ последний "cat"
		dup2(descriptors[pos + 1].fd[1], STDOUT_FILENO);
	close(descriptors[pos].fd[0]);
	close(descriptors[pos].fd[1]);
	ret = handle_commands(); // Выполнить некую КОМАНДУ ("cat" или иное)
	exit(ret);
}

int	handle_pipes(int args_count, char **args, int *position)
{
	int				ret;
	int				pos;
	int				blocks; //Количество БЛОКОВ ("cat" "cat" - значит blocks = 2)
	pid_t			pid;
	t_descriptors	*descriptors;
	ret = EXIT_SUCCESS;
	pos = 0;
	blocks = get_pipes_count(args_count, args) + 1; //Получили количество БЛОКОВ
	descriptors = create_descriptors(blocks);
	if (pipe(descriptors[0].fd) < 0)
		def_err("error: fatal\n", 1);
	while (pos < blocks) //Идем по каждому блоку, т.е сначало на первый cat, а потом на второй cat, если ("cat" "cat")
	{
		if (pos < blocks - 1) //Если НЕ последний "cat"
		{
			if (pipe(descriptors[pos + 1].fd) < 0)
				def_err("error: fatal\n", 1);
		}
		pid = fork();
		if (pid < 0)
			def_err("error: fatal\n", 1);
		if (pid == 0)
			child_body(descriptors, pos, blocks);
		close(descriptors[pos].fd[0]);
		close(descriptors[pos].fd[1]);
		waitpid(pid, &ret, 0);
		pos++;
	}
	free(descriptors);
	return (ret);
}
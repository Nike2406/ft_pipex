#include "../pipex.h"

void	get_exec(t_pipex *s_pp)
{
	int		i;
	char	**cmd;
	int		pid;
	int		exc;

	i = 0;
	cmd = ft_split(s_pp->argv[s_pp->i + 1], ' ');

	// ft_putstr("s_pp.i in get_exec = ");
	// ft_putnbr(s_pp->i);
	// ft_putstr("\n");

	ft_putstr("cmd = ");
	// ft_putstr(s_pp->argv[s_pp->i]);
	ft_putstr(cmd[0]);
	ft_putstr("\n");

	chk_cmd(s_pp, cmd[0]);
	pid = fork();
	if (pid < 0)
		ft_err(4);
	if (pid != 0)
	{
		wait(NULL);
		close(s_pp->pp[s_pp->i - s_pp->hdoc][1]);
	}
	else
	{
		ft_putstr("Execute command: ");
		ft_putstr(s_pp->cmd);
		ft_putstr("\n");
		b_child_process(s_pp);
		// if (s_pp->i == s_pp->argc - 3)
		// 	dup2(s_pp->pp[s_pp->argc - 2][1], 1);
		exc = execve(s_pp->cmd, cmd, NULL);
		if (exc < 0)
			ft_err(7);
	}
}

void	b_child_process(t_pipex *s_pp)
{
	ft_putstr("s_pp.i in b_child = ");
	ft_putnbr(s_pp->i);
	ft_putstr("\n");
	// if (s_pp->i == 0 && !s_pp->hdoc)
	// {
	// 	ft_putstr("WTF0\n");
	// 	dup2(s_pp->pp[0][0], STDIN_FILENO);
	// }
	// else if (s_pp->hdoc && s_pp->i == 2)
	// {
	// 	ft_putstr("WTF1\n");
	// 	dup2(s_pp->pp[0][0], 0);
	// 	dup2(s_pp->pp[s_pp->i - s_pp->hdoc][1], 1);
	// 	close(s_pp->pp[s_pp->i - s_pp->hdoc][0]);
	// 	close(s_pp->pp[0][0]);
	// }
	// else if (s_pp->i == s_pp->argc - 1)
	// {
	// 	ft_putstr("WTF2\n");
	// 	dup2(s_pp->pp[s_pp->i - 1 - s_pp->hdoc][0], 0);
	// 	dup2(s_pp->pp[s_pp->i - s_pp->hdoc][1], 1);
	// 	close(s_pp->pp[s_pp->i - 1 - s_pp->hdoc][1]);
	// 	close(s_pp->pp[s_pp->i - s_pp->hdoc][1]);
	// }
	// else
	// {
	// 	ft_putstr("WTF3\n");
	// 	dup2(s_pp->pp[s_pp->i - 1 - s_pp->hdoc][0], 0);
	// 	dup2(s_pp->pp[s_pp->i - s_pp->hdoc][1], 1);
	// 	close(s_pp->pp[s_pp->i - 1 - s_pp->hdoc][1]);
	// 	close(s_pp->pp[s_pp->i - s_pp->hdoc][0]);
	// }



	if (s_pp->i == 0 && !s_pp->hdoc)
		dup2(s_pp->pp[0][0], STDIN_FILENO);
	else if (s_pp->hdoc && s_pp->i == 2)
	{
		// ft_putnbr(s_pp->i);
		// ft_putstr("\n");
		ft_putstr("First\n");
		close(s_pp->pp[0][1]);
		dup2(s_pp->pp[0][0], STDIN_FILENO);
		// close(s_pp->pp[0][1]);
		// close(s_pp->pp[0][0]);
	}
	else if (s_pp->i < s_pp->argc - 3)
	{
		// ft_putnbr(s_pp->i);
		// ft_putstr("\n");
		// ft_putstr("Second\n");
		if (s_pp->i != 1 || (s_pp->i != 3 && s_pp->hdoc))
		{
			close(s_pp->pp[s_pp->i - 1 - s_pp->hdoc][1]);
			// ft_putstr("I closed the pipe\n");
		}
		// ft_putstr("Third\n");
		dup2(s_pp->pp[s_pp->i - 1 - s_pp->hdoc][0], STDIN_FILENO);
		// ft_putstr("Fourth\n");
		close(s_pp->pp[s_pp->i - s_pp->hdoc][0]);
		// ft_putstr("Fifth\n");
		dup2(s_pp->pp[s_pp->i - s_pp->hdoc][1], STDOUT_FILENO);
		// close(s_pp->pp[s_pp->i - s_pp->hdoc][1]);
		// ft_putstr("Sixth\n");
	}
	else
	{
		// ft_putstr("Seventh\n");
		// ft_putnbr(s_pp->i);
		// ft_putstr("\n");
		close(s_pp->pp[s_pp->i - 1 - s_pp->hdoc][1]);
		dup2(s_pp->pp[s_pp->i - 1 - s_pp->hdoc][0], STDIN_FILENO);
		// ft_putstr("8\n");
		close(s_pp->pp[s_pp->argc - 1][0]);
		dup2(s_pp->pp[s_pp->argc - 2][1], 1);
		close(s_pp->pp[s_pp->i - 1 - s_pp->hdoc][0]);
		// ft_putstr("9\n");
	}
}

void	get_hdoc(t_pipex *s_pp)
{
	char	*buf;
	char	*stop_wrd;

	stop_wrd = s_pp->argv[2];
	s_pp->pp[0][0] = \
		open("input_tmp", O_RDWR | O_APPEND | O_CREAT, 0777);
	if (s_pp->pp[0][0] < 0)
		ft_err(2);
	buf = "";
	// close(s_pp->pp[0][1]);
	while (ft_strncmp(stop_wrd, buf, ft_strlen(stop_wrd) + 1))
	{
		ft_putstr("heredoc>");
		if (get_next_line(0, &buf) && \
				ft_strncmp(stop_wrd, buf, ft_strlen(stop_wrd) + 1))
			{
				write(s_pp->pp[0][0], buf, ft_strlen(buf));
				write(s_pp->pp[0][0], "\n", 1);
			}
		free(buf);
	}
	// close(s_pp->pp[0][0]);
	return ;

	// ft_putstr("I'll try to create\n");
}

void get_open(t_pipex *s_pp)
{
	if (s_pp->hdoc)
	{
		get_hdoc(s_pp);
	}
	else
	{
		s_pp->pp[0][0] = open(s_pp->argv[1], O_RDONLY, 0777);
		if (s_pp->pp[0][0] < 0)
			ft_err(2);
		// ft_putstr("File 1 opened\n");
	}
	if (s_pp->hdoc)
		s_pp->pp[s_pp->argc - 2][1] = \
			open(s_pp->argv[s_pp->argc - 1], O_WRONLY | O_APPEND | O_CREAT, 0777);
	else
		s_pp->pp[s_pp->argc - 2][1] = \
			open(s_pp->argv[s_pp->argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (s_pp->argv[s_pp->argc - 1][1] < 0)
		ft_err(1);
	// ft_putstr("File 2 opened\n");
}

void	get_pipe(t_pipex *s_pp)
{
	int	i;

	i = 0;
	while (i < s_pp->argc + 1)
	{
		pipe(s_pp->pp[i]);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	s_pp;
	// int gnlfd;
	// char	*gnlline;

	if (argc < 5)
		ft_err(1);
	s_pp.argc = argc;
	s_pp.argv = argv;
	get_pipe(&s_pp);
	s_pp.addr = path(envp);

	// gnlfd = open("/Users/prochell/projects/ft_pipex/input", O_RDONLY);
	// while (get_next_line(gnlfd, &gnlline))
	// {
	// 	ft_putstr(gnlline);
	// 	ft_putstr("\n");
	// 	free(gnlline);
	// }
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		s_pp.hdoc = 2;
	else
		s_pp.hdoc = 0;
	s_pp.i = 0 + s_pp.hdoc;
	get_open(&s_pp);
	// b_child_process(&s_pp);
	// ft_putstr("cmd = ");
	// ft_putstr(argv[s_pp.i]);
	// ft_putstr("\n");
	while (++s_pp.i < argc - 2)
	{
		get_exec(&s_pp);
	}
	// get_exec(&s_pp);
	s_pp.i = -1;
	// while (++s_pp.i < s_pp.argc)
	// 	wait(NULL);
	// close(s_pp.pp[0][0]);
	// close(s_pp.pp[argc - 2][1]);
	return (0);
}

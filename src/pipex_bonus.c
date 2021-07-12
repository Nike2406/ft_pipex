#include "../pipex.h"

void	get_exec(t_pipex *s_pp)
{
	int		i;
	char	**cmd;
	int		pid;
	int		exc;

	if (s_pp->hdoc)
		i = 0;
	else
		i = 1;
	cmd = ft_split(s_pp->argv[s_pp->i + i], ' ');
	i = 0;
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
		// if (pid == 0)
		// {
			b_child_process(s_pp);
			exc = execve(s_pp->cmd, cmd, NULL);
			if (exc < 0)
				ft_err(7);
		// }
	}
}

void	b_child_process(t_pipex *s_pp)
{
	if (s_pp->i == 0 && !s_pp->hdoc)
		dup2(s_pp->pp[0][0], STDIN_FILENO);
	else if (s_pp->hdoc && s_pp->i == 2)
	{
		close(s_pp->pp[0][1]);
		dup2(s_pp->pp[0][0], STDIN_FILENO);
	}
	else if (s_pp->i < s_pp->argc - s_pp->jhd - 1)
	{
		close(s_pp->pp[s_pp->i - 1 - s_pp->hdoc][1]);
		dup2(s_pp->pp[s_pp->i - 1 - s_pp->hdoc][0], STDIN_FILENO);
		close(s_pp->pp[s_pp->i - 1 - s_pp->hdoc][0]);
		close(s_pp->pp[s_pp->i - s_pp->hdoc][0]);
		dup2(s_pp->pp[s_pp->i - s_pp->hdoc][1], STDOUT_FILENO);
	}
	else
	{
		close(s_pp->pp[s_pp->i - 1 - s_pp->hdoc][1]);
		dup2(s_pp->pp[s_pp->i - 1 - s_pp->hdoc][0], STDIN_FILENO);
		close(s_pp->pp[s_pp->argc - 1][0]);
		dup2(s_pp->pp[s_pp->argc - 2][1], 1);
		close(s_pp->pp[s_pp->i - 1 - s_pp->hdoc][0]);
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
	return ;
}

void get_open(t_pipex *s_pp)
{
	if (s_pp->hdoc)
		get_hdoc(s_pp);
	else
	{
		s_pp->pp[0][0] = open(s_pp->argv[1], O_RDONLY, 0777);
		if (s_pp->pp[0][0] < 0)
			ft_err(2);
	}
	if (s_pp->hdoc)
		s_pp->pp[s_pp->argc - 2][1] = \
			open(s_pp->argv[s_pp->argc - 1], O_WRONLY | O_APPEND | O_CREAT, 0777);
	else
		s_pp->pp[s_pp->argc - 2][1] = \
			open(s_pp->argv[s_pp->argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (s_pp->argv[s_pp->argc - 1][1] < 0)
		ft_err(1);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	s_pp;

	if (argc < 5)
		ft_err(1);
	s_pp.argc = argc;
	s_pp.argv = argv;
	get_pipe(&s_pp);
	s_pp.addr = path(envp);
	s_pp.hdoc = 0;
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		s_pp.hdoc = 2;
	s_pp.i = 0 + s_pp.hdoc;
	get_open(&s_pp);
	b_child_process(&s_pp);
	s_pp.jhd = 2;
	if (s_pp.hdoc)
		s_pp.jhd = 1;
	s_pp.i = 0 + s_pp.hdoc;
	while (++s_pp.i < argc - s_pp.jhd)
		get_exec(&s_pp);
	// s_pp.i = 0 + s_pp.hdoc;
	// while (++s_pp.i < argc - s_pp.jhd)
	// {
	// 	wait(NULL);
	// 	close(s_pp.pp[s_pp.i - s_pp.hdoc][1]);
	// }
	// while (++s_pp.i < s_pp.argc)
	// 	wait(NULL);
	return (0);
}

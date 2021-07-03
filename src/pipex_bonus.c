#include "../pipex.h"

char	**path(char **envp)
{
	int		i;
	char	**addr;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
			break ;
		i++;
	}
	addr = ft_split(envp[i] + 5, ':');
	i = 0;
	while (addr[i])
	{
		addr[i] = ft_strjoin(addr[i], "/");
		i++;
	}
	return (addr);
}

void	get_exec(t_pipex *s_pp, int j)
{
	int		i;
	char	**cmd;

	i = 0;
	cmd = ft_split(s_pp->argv[j], ' ');
	while (s_pp->addr[i])
	{
		execve(ft_strjoin(s_pp->addr[i], cmd[0]), cmd, NULL);
		i++;
	}
}

void	b_child_process(t_pipex *s_pp)
{
		ft_putstr("Hi!\n");
	if (s_pp->i == 0)
	{
		dup2(s_pp->fd_fl[0], 0);
		dup2(s_pp->pp[s_pp->i][1], 1);
		close(s_pp->pp[s_pp->i][0]);
		close(s_pp->fd_fl[0]);
	}
	else if (s_pp->i == s_pp->cmd_numb - 1)
	{
		dup2(s_pp->pp[s_pp->i - 1][0], 0);
		dup2(s_pp->fd_fl[1], 1);
		close(s_pp->pp[s_pp->i - 1][1]);
		close(s_pp->fd_fl[1]);
	}
	else
	{
		dup2(s_pp->pp[s_pp->i - 1][0], 0);
		dup2(s_pp->pp[s_pp->i][1], 1);
		close(s_pp->pp[s_pp->i - 1][1]);
		close(s_pp->pp[s_pp->i][0]);
	}
	get_exec(s_pp, s_pp->i);
}


// void	b_parent_process(t_pipex *s_pp, char **argv, int *fd_fl)
// {

// 	close(fd_pp[1]);
// 	dup2(fd_pp[0], 0);
// 	dup2(fd_fl[1], 1);
// 	close(fd_pp[0]);
// 	get_exec(s_pp, argv, 3);
// 	wait(NULL);
// }

void get_open(t_pipex *s_pp)
{
	s_pp->fd_fl[0] = open(s_pp->argv[1], O_RDONLY, 0777);
	if (s_pp->fd_fl[0] < 0)
		ft_err(2);
	s_pp->fd_fl[1] = open(s_pp->argv[s_pp->argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (s_pp->fd_fl[1] < 0)
		ft_err(1);
}

void	ft_err(int	code)
{
	if (code == 1)
		ft_putstr("Please, add more data.\n");
	else if (code == 2)
		ft_putstr("Error to open input file.\n");
	else if (code == 3)
		ft_putstr("Error to open the pipe.\n");
	else if (code == 4)
		ft_putstr("Fork failed.\n");
	else if (code == 5)
		ft_putstr("Malloc failed.\n");
	exit(code);
}

void	get_pipe(t_pipex *s_pp)
{
	int	i;

	i = 0;
	// *s_pp->pp = malloc(sizeof(int *) * i);
	// if (!*s_pp->pp)
	// 	ft_err(5);
	while (i < s_pp->cmd_numb - 1)
	{
		// s_pp->pp[i] = malloc(sizeof(int) * 2);
		if (pipe(s_pp->pp[i]) < 0)
			ft_err(2);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		pid;
	t_pipex	s_pp;

	s_pp.i = -1;
	if (argc < 5)
		ft_err(1);
	s_pp.argc = argc;
	s_pp.argv = argv;
	get_open(&s_pp);
	s_pp.cmd_numb = argc - 3;
	s_pp.addr = path(envp);
	while (++s_pp.i < s_pp.cmd_numb)
	{
		get_pipe(&s_pp);
		pid = fork();
		if (pid < 0)
			ft_err(4);
		if (pid == 0)
			b_child_process(&s_pp);
		// else
		// 	b_parent_process(&s_pp, argv, fd_fl);
	}
	s_pp.i = -1;
	while (++s_pp.i < s_pp.cmd_numb)
		wait(NULL);
	return (0);
}

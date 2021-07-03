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

void	get_exec(t_pipex *s_pp, char **argv, int j)
{
	int		i;
	char	**cmd;

	i = 0;
	cmd = ft_split(argv[j], ' ');
	while (s_pp->addr[i])
	{
		execve(ft_strjoin(s_pp->addr[i], cmd[0]), cmd, NULL);
		i++;
	}
	i = 0;
	while (cmd[i])
		cmd[i++] = NULL;
	free(cmd);
}

void	b_child_process(t_pipex *s_pp, char **argv, int *fd_pp, int *fd_fl)
{
	close(fd_pp[0]);
	dup2(fd_fl[0], 0);
	dup2(fd_pp[1], 1);
	close(fd_pp[1]);
	get_exec(s_pp, argv, 2);
}


void	b_parent_process(t_pipex *s_pp, char **argv, int *fd_pp, int *fd_fl)
{
	fd_fl[1] = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd_fl[1] < 0)
		ft_err(1, s_pp);
	close(fd_pp[1]);
	dup2(fd_pp[0], 0);
	dup2(fd_fl[1], 1);
	close(fd_pp[0]);
	get_exec(s_pp, argv, 3);
	wait(NULL);
}

void	ft_err(int	code, t_pipex *s_pp)
{
	if (code == 1)
	{
		ft_putstr("Please, add more data.\n");
		free(s_pp);
		exit(code);
	}
	else if (code == 2)
	{
		ft_putstr("Error to open input file.\n");
		free(s_pp);
		exit(code);
	}
	else if (code == 3)
	{
		ft_putstr("Error to open the pipe.\n");
		free(s_pp);
		exit(code);
	}
	else if (code == 4)
	{
		ft_putstr("Fork failed.\n");
		free(s_pp);
		exit(code);
	}
}

void	get_pipe(t_pipex *s_pp)
{
	int	i;

	i = 0;
	while (i < s_pp->cmd_numb - 1)
	{
		if (pipe(fd_pp[i]) < 0)
			ft_err(2, s_pp);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		fd_fl[2];
	int		pid;
	int		fd_pp[2];
	t_pipex	*s_pp;

	s_pp = (t_pipex *)malloc(sizeof(t_pipex));
	if (argc < 5)
		ft_err(1, s_pp);
	s_pp->cmd_numb = argc - 3;
	s_pp->addr = path(envp);
	fd_fl[0] = open(argv[1], O_RDONLY, 0777);
	if (fd_fl[0] < 0)
		ft_err(2, s_pp);
	if (pipe(fd_pp) < 0)
		ft_err(3, s_pp);
	pid = fork();
	if (pid < 0)
		ft_err(4, s_pp);
	if (pid == 0)
		b_child_process(s_pp, argv, fd_pp, fd_fl);
	else
		b_parent_process(s_pp, argv, fd_pp, fd_fl);
	free(s_pp);
	return (0);
}

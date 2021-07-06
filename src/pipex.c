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

void	child_process(char **addr, char **argv, int *fd_pp, int *fd_fl)
{
	int		i;
	char	**cmd;

	i = 0;
	close(fd_pp[0]);
	dup2(fd_fl[0], 0);
	dup2(fd_pp[1], 1);
	close(fd_pp[1]);
	cmd = ft_split(argv[2], ' ');
	while (addr[i])
	{
		execve(ft_strjoin(addr[i], cmd[0]), cmd, NULL);
		i++;
	}
	i = 0;
	while (cmd[i])
		cmd[i++] = NULL;
	free(cmd);
}

void	parent_process(char **addr, char **argv, int *fd_pp, int *fd_fl)
{
	int		i;
	char	**cmd;

	i = 0;
	fd_fl[1] = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd_fl[1] < 0)
		ft_err(1);
	close(fd_pp[1]);
	dup2(fd_pp[0], 0);
	dup2(fd_fl[1], 1);
	close(fd_pp[0]);
	i = 0;
	cmd = ft_split(argv[3], ' ');
	while (addr[i])
	{
		execve(ft_strjoin(addr[i], cmd[0]), cmd, NULL);
		i++;
	}
	i = 0;
	while (cmd[i])
		cmd[i++] = NULL;
	free(cmd);
	wait(NULL);
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
	exit(code);
}

int	main(int argc, char **argv, char **envp)
{
	char	**addr;
	int		fd_fl[2];
	int		pid1;
	int		fd_pp[2];

	if (argc < 5)
		ft_err(1);
	addr = path(envp);
	fd_fl[0] = open(argv[1], O_RDONLY, 0777);
	if (fd_fl[0] < 0)
		ft_err(2);
	if (pipe(fd_pp) < 0)
		ft_err(3);
	pid1 = fork();
	if (pid1 < 0)
		ft_err(4);
	if (pid1 == 0)
		child_process(addr, argv, fd_pp, fd_fl);
	else
		parent_process(addr, argv, fd_pp, fd_fl);
	free(addr);
	return (0);
}

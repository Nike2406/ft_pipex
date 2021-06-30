#include "../pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	i;
	char	**addr;
	char	**cmd;
	int		fd_fl[2];
	int		pid1;
	int		fd_pp[2];

	i = 2;
	if (argc < 5)
	{
		ft_putstr("Please, add more data.");
		return (1);
	}

	// Поиск путей
	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
			break;
		i++;
	}
	addr = ft_split(envp[i] + 5, ':');

	i = 0;
	while (addr[i])
	{
		addr[i] = ft_strjoin(addr[i], "/");
		i++;
	}
	fd_fl[0] = open(argv[1], O_RDONLY, 0777);
	if (fd_fl[0] < 0)
		return 1;
	if (pipe(fd_pp) < 0)
		return 1;
	pid1 = fork();
	if (pid1 < 0)
		return 1;
	if (pid1 == 0)
	{
		close(fd_pp[0]);
		dup2(fd_fl[0], 0);
		dup2(fd_pp[1], 1);
		close(fd_pp[1]);
		i = 0;
		cmd = ft_split(argv[2], ' ');
		while (addr[i])
		{
			execve(ft_strjoin(addr[i], cmd[0]), cmd, NULL);
			i++;
		}
	}
	else
	{
		fd_fl[1] = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0777);
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
		wait(NULL);
	}

	return (0);
}
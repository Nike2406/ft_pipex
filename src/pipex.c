#include "pipex.h"

// void	pipe(char **path, char **argv)
// {

// }

int	main(int argc, char **argv, char **envp)
{
	int	i;
	// (void)argc;
	// (void)argv;
	char	**addr;
	char	**cmd;
	int		fd[4];
	int		pid1;
	int		pid2;

	i = 1;
	if (argc < 2)
	{
		ft_putstr("Please, add more data.");
		return (1);
	}
	// ????? Check flags and other cmnds
	while (i < argc)
	{
		cmd = ft_split(argv[i], ' ');
		ft_putstr(cmd[i - 1]);
		i++;
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

	if (pipe(fd) < 0)
		return (2);
	pid1 = fork();
	if (pid1 < 0)
		return (3);
	if (pid1 == 0)
	{
		// Child process
		close(fd[1]);
		fd[0] = open(argv[1], O_RDONLY, 0666);
		dup2(fd[0], STDOUT_FILENO);

	}


	// Разделение путей
	i = 0;
	while (addr[i])
	{
		addr[i] = ft_strjoin(addr[i], "/");
		execve(ft_strjoin(addr[i], cmd[0]), cmd, NULL);
		i++;
	}

	return (0);
}
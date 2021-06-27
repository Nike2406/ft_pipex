#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	i;
	(void)argc;
	(void)argv;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
			break;
		i++;
	}
	ft_putstr(envp[i]);
	return (0);
}
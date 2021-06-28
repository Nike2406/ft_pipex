#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	i;
	(void)argc;
	(void)argv;
	char	**arr;


	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
			break;
		i++;
	}
	arr = ft_split(envp[i] + 5, ':');

	i = 0;
	while (arr[i])
	{
		ft_putstr(ft_strjoin(arr[i], "/"));
		ft_putchar('\n');
		i++;
	}
	return (0);
}
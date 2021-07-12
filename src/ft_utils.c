#include "../pipex.h"

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
	else if (code == 6)
		ft_putstr("Wrong command.\n");
	else if (code == 7)
		ft_putstr("Execute failed.\n");
	else if (code == 8)
		ft_putstr("Pipe failed.\n");
	else
		ft_putstr("Unexpected error.\n");
	exit(code);
}

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

void	chk_cmd(t_pipex *s_pp, char *cmd)
{
	int		i;
	int		acss;
	char	*tmp;

	i = 0;
	acss = 0;
	while (s_pp->addr[i])
	{
		s_pp->cmd = ft_strjoin(s_pp->addr[i], cmd);
		tmp = s_pp->cmd;
		acss = access(s_pp->cmd, 1);
		if (acss >= 0)
			return ;
		i++;
		free(tmp);
	}
	if (acss == -1)
		ft_err(6);
}

void	get_pipe(t_pipex *s_pp)
{
	int	i;

	i = 0 + s_pp->hdoc;
	while (i < s_pp->argc - s_pp->jhd)
	{
		pipe(s_pp->pp[i]);
		i++;
	}
}

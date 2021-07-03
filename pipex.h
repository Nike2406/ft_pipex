#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdio.h>

typedef struct s_pipex
{
	char	**addr;
	int		cmd_numb;
}	t_pipex;

char	**path(char **envp);
void	child_process(char **addr, char **argv, int *fd_pp, int *fd_fl);
void	parent_process(char **addr, char **argv, int *fd_pp, int *fd_fl);
void	b_child_process(t_pipex *s_pp, char **argv, int *fd_pp, int *fd_fl);
void	b_parent_process(t_pipex *s_pp, char **argv, int *fd_pp, int *fd_fl);
void	ft_err(int	code, t_pipex *s_pp);

#endif
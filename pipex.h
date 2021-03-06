#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdio.h>
# include "./get_next_line/get_next_line.h"

typedef struct s_pipex
{
	char	**addr;
	int		pp[100][2];
	int		argc;
	char	**argv;
	int		i;
	char	*cmd;
	int		hdoc;
}	t_pipex;

char	**path(char **envp);
void	child_process(char **addr, char **argv, int *fd_pp, int *fd_fl);
void	parent_process(char **addr, char **argv, int *fd_pp, int *fd_fl);
void	b_child_process(t_pipex *s_pp);
void	b_parent_process(t_pipex *s_pp, int *fd_fl);
void	ft_err(int	code);
void	get_open(t_pipex *s_pp);
void	chk_cmd(t_pipex *s_pp, char *cmd);

#endif
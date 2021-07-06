NAME 		= pipex
FLAGS		= -Wall -Wextra -Werror
CFLAGS		= $(FLAGS) -I.
CC			= gcc
OBJS	 	= $(SRCS:%.c=%.o)
OBJS_BONUS 	= $(SRCS_BONUS:%.c=%.o)
LIBFT_OBJS	= $(LIBFT:%.c=%.o)
SRCS 		= src/pipex.c
SRCS_BONUS 	= src/pipex_rerun.c

.PHONY: all clean fclean re bonus libft norm

.o: .c
	$(CC) $(CFLAGS) $< -o $@

all: libft $(NAME)

${NAME}: $(OBJS) pipex.h
	$(CC) $(OBJS) -Llibft -lft -o $(NAME)

bonus: libft $(OBJS_BONUS) pipex.h
	$(CC) $(OBJS_BONUS) -Llibft -lft -o $(NAME)

norm:
	norminette $(SRCS)
	norminette pipex.h
	make -C libft/ norm

libft:
	make lib -C libft

clean:
	rm -f $(OBJS)
	rm -f $(OBJS_BONUS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	rm -f libft/libft.a

re: fclean all

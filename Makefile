NAME 		= pipex
FLAGS		= -Wall -Wextra -Werror
CFLAGS		= $(FLAGS) -I.
CC			= gcc
OBJS	 	= $(SRCS:%.c=%.o)
LIBFT_OBJS	= $(LIBFT:%.c=%.o)
SRCS 		= src/pipex.c

.PHONY: all clean fclean re bonus libft norm

.o: .c
	$(CC) $(CFLAGS) $< -o $@

all: libft $(NAME)

${NAME}: $(OBJS) pipex.h
	$(CC) $(OBJS) -Llibft -lft -o $(NAME)

norm:
	norminette $(SRCS)
	norminette pipex.h
	make -C libft/ norm

libft:
	make lib -C libft

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	rm -f libft/libft.a

re: fclean all

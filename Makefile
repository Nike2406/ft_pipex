NAME 		= libftprintf.a
CFLAGS		= -Wall -Wextra -Werror
CC			= gcc
OBJS	 	= ${SRCS:.c=.o}
LIBFT_OBJS	= ${LIBFT:.c=.o}
INCLUDE 	= ./includes/ft_printf.h \
			./libft/libft.h
SRCS 		= src/pipex.c
LIBFT		=

.c.o:
	@${CC} ${CFLAGS} -c $< -o $@

all: ${NAME}

${NAME}: ${OBJS} $(LIBFT_OBJS) ${INCLUDE}
	@ar rcs ${NAME} $(LIBFT_OBJS) $?

norm:
	norminette .

test_c:
	@$(CC) test3.c $(LIBFT) $(SRCS) -I $(INCLUDE) && ./a.out | cat -e

clean:
	@/bin/rm -f ${OBJS}
	@/bin/rm -f ${LIBFT_OBJS}
	@/bin/rm -f a.out

fclean: clean
	@/bin/rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus

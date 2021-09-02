NAME 		= pipex
FLAGS		= -Wall -Wextra -Werror
CFLAGS		= $(FLAGS) -I.
CC			= gcc

ifeq ($(MAKECMDGOALS),bonus)
	OBJS = $(SRCS_BONUS:%.c=%.o)
else
	OBJS = $(SRCS:%.c=%.o)
endif

LIBFT_OBJS	= $(LIBFT:%.c=%.o)
SRCS 		= src/pipex.c\
			get_next_line/get_next_line.c \
			src/ft_utils.c
SRCS_BONUS 	= src/pipex_bonus.c \
			get_next_line/get_next_line.c \
			src/ft_utils.c
INCLUDE		= pipex.h \
			get_next_line/get_next_line.h
LIBFT_A		= libft/libft.a

.PHONY: all clean fclean re bonus libft norm

.o: .c $(INCLUDE)
	$(CC) $(CFLAGS) $< -o $@

all: libft $(NAME)

${NAME}: $(OBJS) $(INCLUDE)
	$(CC) $(OBJS) $(LIBFT_A) -o $(NAME)

bonus: libft $(NAME)

norm:
	norminette $(SRCS)
	norminette $(INCLUDE)
	make -C libft/ norm

libft:
	make lib -C libft

clean:
	rm -f get_next_line/*.o
	rm -f src/*.o
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	rm -f libft/libft.a

re: fclean all

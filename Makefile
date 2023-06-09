NAME = minishell

CFILES = minishell.c syntax_errors.c split.c redirections.c token.c

LIBFT = ./libft/libft.a

OBJ = ${CFILES:.c=.o}

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

CC = cc

all : ${NAME}

${NAME} : ${OBJ}
	make -C libft
	${CC} ${OBJ} ${CFLAGS} ${LIBFT} -lreadline -o ${NAME}

clean:
	make clean -C libft
	${RM} ${OBJ}

fclean: clean
	make fclean -C libft
	${RM} ${NAME}

re : fclean all
	
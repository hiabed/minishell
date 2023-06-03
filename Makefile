NAME = minishell

CFILES = minishell.c syntax_errors.c split.c redirections.c

LIBFT = ./libft/libft.a

OBJ = ${CFILES:.c=.o}

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

CC = cc

all : ${NAME}

${NAME} : ${OBJ}
	${CC} ${OBJ} ${CFLAGS} ${LIBFT} -lreadline -o ${NAME}

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

re : fclean all
	
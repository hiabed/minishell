NAME = minishell

CFILES = minishell.c syntax_errors.c split.c redirections.c token.c split_spaces.c\
		expand.c space_arround_red.c ft_strcmp.c lengths.c expand_helpers2.c signals.c\
		expand_helpers.c heredoc.c fill_words.c helpers.c split_helper.c errors_helper.c \
		./execution/ft_echo.c ./execution/linked.c ./execution/ft_pwd.c ./execution/ft_export.c \
		./execution/ft_sort.c ./execution/builtins.c ./execution/ft_export_util.c \
		./execution/ft_cd.c ./execution/ft_unset.c ./execution/ft_exit.c ./execution/ft_env.c \
		./execution/ft_Error.c ./execution/main_ex.c ./execution/main_ex_continued.c \
		get_next_line.c get_next_line_utils.c expand_helpers3.c helpers2.c ./execution/main_ex_helpers.c \

LIBFT = ./libft/libft.a

OBJ = ${CFILES:.c=.o}

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3

LIB = -lreadline -L /Users/mhassani/goinfre/.brew/opt/readline/lib -I /Users/mhassani/goinfre/.brew/opt/readline/lib

CC = cc

all : ${NAME}

${NAME} : ${OBJ}
	${CC} ${OBJ} ${CFLAGS} ${LIB} ${LIBFT} -o ${NAME}
	stty -echoctl

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

re : fclean all

NAME = pipex

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

MAIN_SRC = pipex.c

MAIN_OBJ = ${MAIN_SRC:.c=.o}

%.o:%.c pipex.h
	$(CC) $(CFLAGS) -c $< -o $@

all: ${NAME}

${NAME}: ${MAIN_OBJ} libft/libft.a
		${CC} ${CFLAGS} ${MAIN_OBJ} -Llibft -lft -o ${NAME}

libft/libft.a:
		make -C libft

clean:
		${RM} ${MAIN_OBJ}
		make -C libft fclean

fclean: clean
		${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re libft

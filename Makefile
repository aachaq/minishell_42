SHELL = /bin/bash
NAME = minishell

READLINE = ${HOME}/goinfre/homebrew/opt/readline
READLINE_INCLUDE = ${READLINE}/include

LIBFT_D = ./libft

INCLUDE = ./include
SRC_D = ./srcs

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I${INCLUDE} -I${READLINE_INCLUDE} 
LDFLAGS = -lreadline -L${READLINE}/lib -lreadline -L${LIBFT_D} 
AR = ar rcs
RM = rm -rf
SRC_PATH = src
SRC_FILES = main/main.c main/signal.c main/termios.c builtin/cd.c builtin/echo.c \
       builtin/env.c  builtin/exit.c builtin/export.c \
	   builtin/pwd.c builtin/unset.c builtin/utils.c builtin/utils1.c \
	   execution/execution.c execution/external_cmd.c execution/redirection.c \
	   execution/utils.c parsing/parser.c \
	   parsing/ft_malloc.c  parsing/lexer.c  	 \
	   parsing/lexer_utils1.c	 parsing/token.c   \
	   parsing/traiter_string.c  parsing/traiter_string1.c \
	   parsing/traiter_string2.c parsing/traiter_string3.c \
	   parsing/lexer_utils.c  parsing/here_document.c parsing/cmd.c 
SRC = ${addprefix ${SRC_PATH}/ , ${SRC_FILES}}
OBJ_FILES = $(SRC_FILES:%.c=%.o)
OBJ = $(addprefix $(SRC_PATH)/, $(OBJ_FILES))

all : ${NAME}


${NAME}: ${OBJ}
	@make bonus -C ${LIBFT_D}
	${CC} ${LDFLAGS} -g -o ${NAME} ${OBJ} libft/libft.a

clean:
	@make clean -C ${LIBFT_D} 
	@$(RM) $(OBJ)

fclean: clean
	@make -C ${LIBFT_D} fclean
	@${RM} ${NAME}

re: fclean
	@make all

.PHONY: all clean fclean re
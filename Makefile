# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgrunho- <tgrunho-@student.42.fr>>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/02 15:42:27 by macampos          #+#    #+#              #
#    Updated: 2024/07/14 17:18:13 by tgrunho-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = src/main.c src/starting_shell.c parsing/parsargs.c parsing/pars_helpers.c parsing/builtins/cd.c parsing/builtins/echo.c parsing/builtins/env.c parsing/builtins/pwd.c parsing/builtins/export.c \
		parsing/builtins/unset.c parsing/builtins/exit.c parsing/utils.c parsing/signals.c  parsing/utils2.c \

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -g

CC = cc

$(NAME): $(OBJ)
	$(MAKE) -C ./includes/libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L./includes/libft -lft -lm -lreadline

all: $(NAME)

clean:
	cd includes/libft && make clean
	rm -rf $(OBJ)

fclean: clean
	cd includes/libft && make fclean
	rm -rf $(NAME)

norminette:
	python3 -m c_formatter_42 $(SRC) includes/minishell.h
	python3 -m norminette $(SRC) includes/minishell.h

valgrind: $(NAME)
	valgrind --suppressions=readline.supp --leak-check=full --track-fds=yes --track-origins=yes --show-leak-kinds=all ./${NAME}
#valgrind --suppressions=readline.supp --tool=memcheck --tool=callgrind  --track-fds=yes ./${NAME}

re: fclean all
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/14 09:29:30 by yloutfi           #+#    #+#              #
#    Updated: 2023/04/03 02:43:27 by yloutfi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3
DFLAGS = -Llibft -lft
CC = cc

SRCS = ./sources/pipex.c

SRCS_BONUS = ./bonus/pipex_bonus.c

HELPERS = ./helpers/parser.c ./helpers/init.c ./helpers/helpers.c			\
	./get_next_line/get_next_line.c	./get_next_line/get_next_line_utils.c 	\
	./helpers/free.c ./get_next_line/gnl_helper.c

OBJS = pipex.o

OBJS_BONUS = pipex_bonus.o

OBJS_HELPERS = init.o helpers.o free.o parser.o get_next_line_utils.o		\
	get_next_line.o gnl_helper.o

all: libft $(OBJS)

libft:
	@$(MAKE) -C libft -s
	
$(OBJS): $(HELPERS) $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS) $(HELPERS)
	@rm -rf pipex_bonus.o
	$(CC) $(CFLAGS) $(DFLAGS) $(OBJS) $(OBJS_HELPERS) -o $(NAME)

bonus: libft $(OBJS_BONUS)

$(OBJS_BONUS) : $(HELPERS) $(SRCS_BONUS)
	$(CC) $(CFLAGS) -c $(SRCS_BONUS) $(HELPERS)
	@rm -rf pipex.o
	$(CC) $(CFLAGS) $(DFLAGS) $(OBJS_BONUS) $(OBJS_HELPERS) -o $(NAME)

clean:
	@$(MAKE) -C libft clean -s
	-rm -f $(OBJS) $(OBJS_BONUS) $(OBJS_HELPERS)

fclean: clean
	@$(MAKE) -C libft fclean -s
	-rm -f $(NAME)

re: fclean all

.PHONY : all libft bonus clean fclean re

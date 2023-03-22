# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/14 09:29:30 by yloutfi           #+#    #+#              #
#    Updated: 2023/03/22 16:05:31 by yloutfi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g
DFLAGS = -Llibft -lft
CC = cc

SRCS = ./sources/pipex.c

SRCS_BONUS = ./bonus/pipex_bonus.c ./get_next_line/get_next_line.c	\
	./get_next_line/get_next_line_utils.c

HELPERS = ./helpers/parser.c ./helpers/init.c ./helpers/helpers.c 	\
	./helpers/free.c

OBJS = pipex.o

OBJS_BONUS = pipex_bonus.o get_next_line.o get_next_line_utils.o

OBJS_HELPERS = init.o helpers.o free.o parser.o

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

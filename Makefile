# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/14 09:29:30 by yloutfi           #+#    #+#              #
#    Updated: 2023/03/14 09:47:05 by yloutfi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g
DFLAGS = -Llibft -lft
CC = cc

SRCS = ./sources/pipex.c ./helpers/parser.c ./helpers/init.c

SRCS_BONUS = ./bonus/pipex_bonus.c

HELPERS = 

OBJS = pipex.o parser.o init.o

OBJS_BONUS = pipex_bonus.o

OBJS_HELPERS = 

all: libft $(OBJS)

libft:
	@$(MAKE) -C libft -s
	
$(OBJS): $(HELPERS) $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)
	@rm -rf pipex_bonus.o
	$(CC) $(CFLAGS) $(DFLAGS) $(OBJS) $(HELPERS) -o $(NAME)

bonus: $(OBONUS)

$(OBJS_BONUS) : $(HELPERS) $(SRCS_BONUS)
	$(CC) $(CFLAGS) -c $(SRCS_BONUS)
	@rm -rf pipex.o
	$(CC) $(CFLAGS) $(DFLAGS) $(OBJS_BONUS) $(HELPERS) -o $(NAME)

clean:
	@$(MAKE) -C libft clean -s
	-rm -f $(OBJS) $(OBJS_BONUS) $(HELPERS)

fclean: clean
	@$(MAKE) -C libft fclean -s
	-rm -f $(NAME)

re: fclean all

.PHONY : all libft bonus clean fclean re
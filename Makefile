# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yloutfi <yloutfi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/14 09:29:30 by yloutfi           #+#    #+#              #
#    Updated: 2023/03/15 08:09:34 by yloutfi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CFLAGS = #-Wall -Wextra -Werror #-fsanitize=address -g
DFLAGS = -Llibft -lft
CC = cc

SRCS = ./sources/pipex.c

SRCS_BONUS = ./bonus/pipex_bonus.c

HELPERS = ./helpers/parser.c ./helpers/init.c ./helpers/helpers.c

OBJS = pipex.o

OBJS_BONUS = pipex_bonus.o

OBJS_HELPERS = parser.o init.o helpers.o

all: libft $(OBJS)

libft:
	@$(MAKE) -C libft -s
	
$(OBJS): $(HELPERS) $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS) $(HELPERS)
	@rm -rf pipex_bonus.o
	$(CC) $(CFLAGS) $(DFLAGS) $(OBJS) $(OBJS_HELPERS) -o $(NAME)

bonus: $(OBJS_BONUS)

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
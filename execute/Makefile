# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/21 17:59:40 by yaboukir          #+#    #+#              #
#    Updated: 2025/04/21 18:23:39 by yaboukir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_MINISHELL = minishell.c ft_helpers.c

OBJS_MINISHELL = $(SRCS_MINISHELL:.c=.o)

CC = cc
AR = ar r
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
INCLUDE = minishell.h
NAME_MINISHELL = minishell

all: $(NAME_MINISHELL)

$(NAME_MINISHELL): $(OBJS_MINISHELL)
	$(CC) $(CFLAGS) $(OBJS_MINISHELL) -lreadline -o $(NAME_MINISHELL)

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS_MINISHELL)

fclean: clean
	$(RM) $(NAME_MINISHELL)

re: fclean all

.PHONY: fclean re all

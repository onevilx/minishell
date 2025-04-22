SRCS_MINISHELL =    mian/main.c utils/utils.c

OBJS_MINISHELL = $(SRCS_MINISHELL:.c=.o)
CC = cc
AR = ar r
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
INCLUDE = includes/minishell.h
NAME_MINISHELL = minishell

all: $(NAME_MINISHELL)

$(NAME_MINISHELL): $(OBJS_MINISHELL)
	$(CC) $(CFLAGS) $(OBJS_MINISHELL)  -lreadline -o $(NAME_MINISHELL)

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS_MINISHELL)

fclean: clean
	$(RM) $(NAME_MINISHELL)

re: fclean all

.PHONY: fclean re all

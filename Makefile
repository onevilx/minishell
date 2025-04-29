SRCS_MINISHELL = main.c parsing/parser.c execution/builtins.c execution/init_builtins1.c execution/init_builtins2.c execution/init_builtins3.c ft_helpers/ft_split.c \
				ft_helpers/utils_pars1.c ft_helpers/utils_pars2.c ft_helpers/utils_pars3.c ft_helpers/utils_exe1.c ft_helpers/utils_exe2.c ft_helpers/utils_exe3.c \
				ft_helpers/global_funcs1.c ft_helpers/global_funcs2.c ft_helpers/global_funcs3.c signals/signals.c execution/execution.c parsing/syntax.c \

OBJS_MINISHELL = $(SRCS_MINISHELL:.c=.o)
CC = cc
AR = ar r
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -I$(HOME)/.local/include
LDFLAGS = -L$(HOME)/.local/lib
INCLUDE = includes/minishell.h includes/protos.h
NAME_MINISHELL = minishell

all: $(NAME_MINISHELL)

$(NAME_MINISHELL): $(OBJS_MINISHELL)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS_MINISHELL) -lreadline -o $(NAME_MINISHELL)

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS_MINISHELL)

fclean: clean
	$(RM) $(NAME_MINISHELL)

re: fclean all

.PHONY: fclean re all

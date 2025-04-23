SRCS_MINISHELL = main.c ft_helpers/utils_pars1.c ft_helpers/utils_exe1.c ft_helpers/utils_exe2.c execution/builtins.c execution/init_builtins1.c execution/init_builtins2.c execution/init_builtins3.c \
				ft_helpers/utils_pars2.c ft_helpers/utils_parc3.c ft_helpers/utils_pars4.c parsing/parser.c ft_helpers/ft_cutom_split.c \

OBJS_MINISHELL = $(SRCS_MINISHELL:.c=.o)
CC = cc
AR = ar r
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
INCLUDE = includes/minishell.h execution/execution.h
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

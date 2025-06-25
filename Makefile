SRCS_MINISHELL = main.c parsing/parser.c execution/builtins.c execution/init_builtins1.c execution/init_builtins2.c execution/init_builtins3.c \
				ft_helpers/utils_pars1.c ft_helpers/utils_pars2.c ft_helpers/utils_pars3.c ft_helpers/utils_exe1.c ft_helpers/utils_exe2.c ft_helpers/utils_exe3.c \
				ft_helpers/global_funcs1.c ft_helpers/global_funcs2.c ft_helpers/global_funcs3.c signals/signals.c execution/execution.c parsing/syntax.c \
				parsing/ft_parse_commands.c execution/redirections.c execution/pipes.c ft_helpers/utils_exe4.c ft_helpers/utils_exe5.c ft_helpers/utils_exe6.c ft_helpers/utils_exe7.c \
				ft_helpers/utils_pars4.c ft_helpers/utils_signals.c parsing/ft_expand_tokens.c parsing/ft_init_env.c ft_helpers/utils_exe8.c ft_helpers/global_funcs4.c \
				ft_helpers/ft_costum_split.c ft_helpers/utils_exe9.c ft_helpers/global_funcs5.c ft_helpers/utils_exe10.c ft_helpers/utils_exe11.c ft_helpers/gc_malloc.c parsing/ft_remove_empty.c \
				ft_helpers/utils_pars5.c ft_helpers/utils_pars6.c ft_helpers/utils_pars7.c ft_helpers/utils_pars8.c ft_helpers/utils_pars9.c ft_helpers/utils_pars10.c  ft_helpers/utils_pars11.c \

OBJS_MINISHELL = $(SRCS_MINISHELL:.c=.o)
CC = cc
AR = ar r
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g -I$(HOME)/.local/include #-fsanitize=address 
LDFLAGS = -L$(HOME)/.local/lib
INCLUDE = includes/minishell.h includes/protos.h
NAME_MINISHELL = minishell

all: $(NAME_MINISHELL)

$(NAME_MINISHELL): $(OBJS_MINISHELL)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS_MINISHELL) -lreadline -lncurses -o $(NAME_MINISHELL)

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS_MINISHELL)

fclean: clean
	$(RM) $(NAME_MINISHELL)

re: fclean all

.PHONY: fclean re all

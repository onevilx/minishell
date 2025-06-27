/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:30:28 by obouftou          #+#    #+#             */
/*   Updated: 2025/06/27 01:21:06 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/protos.h"

int	g_signal = 0;

void	gc_free_all(void)
{
	static t_gc	*list = NULL;
	t_gc		*tmp;

	while (list)
	{
		free(list->ptr);
		tmp = list;
		list = list->next;
		free(tmp);
	}
}

static void	run_command(char *input, int *exit_status)
{
	t_cmd	*cmd;

	add_history(input);
	cmd = ft_input_proces(input, *get_env(), get_exit_status());
	if (cmd)
	{
		*get_shell_mode() = CHILD_RUNNING;
		*exit_status = execute_command(cmd);
		*get_shell_mode() = NORMAL;
	}
	gc_free_all();
}

static void	shell_loop(struct termios *term, int *exit_status)
{
	char	*input;

	while (1)
	{
		*get_shell_mode() = NORMAL;
		tcgetattr(STDIN_FILENO, term);
		input = readline("minishell$ ");
		if (!input)
			sigterm_handler(*get_exit_status());
		if (*input)
			run_command(input, exit_status);
		tcsetattr(STDIN_FILENO, TCSANOW, term);
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	struct termios	term;
	int				exit_status;

	(void)argc;
	(void)argv;
	init_env(envp);
	exit_status = 0;
	shell_loop(&term, &exit_status);
	return (exit_status);
}

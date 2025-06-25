/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:30:28 by obouftou          #+#    #+#             */
/*   Updated: 2025/06/25 20:46:26 by yaboukir         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_cmd	*cmd;
	int		exit_status;

	struct termios	term;
	// if (!isatty(1) || !isatty(0))
	// 	return (1);
	exit_status = 0;
	((void) argc, (void) argv, init_env(envp));
	while (1)
	{
		tcgetattr(STDIN_FILENO, &term);
		input = readline("minishell$ ");
		if (!input)
			sigterm_handler(*get_exit_status());
		if (*input)
		{
			add_history(input);
			cmd = ft_input_proces(input, *get_env(), get_exit_status());
			if (cmd)
				exit_status = execute_command(cmd);
			gc_free_all();
		}
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		free(input);
	}
	return (exit_status);
}

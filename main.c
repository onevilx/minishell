/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouftou <obouftou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:30:28 by obouftou          #+#    #+#             */
/*   Updated: 2025/06/20 18:29:42 by obouftou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/protos.h"

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

	// if (!isatty(1) || !isatty(0))
		// return (1);
	exit_status = 0;
	(void)argc;
	(void)argv;
	init_env(envp);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			sigterm_handler(0);
		if (*input)
		{
			add_history(input);
			cmd = ft_input_proces(input, *get_env(), get_exit_status());
			if (cmd)
				exit_status = execute_command(cmd);
			
			// free_cmd(cmd);
		}
		free(input);
	}
	return (exit_status);
}

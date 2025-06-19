/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:30:28 by obouftou          #+#    #+#             */
/*   Updated: 2025/06/19 22:05:28 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/protos.h"

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
			// printf("------------------------------------------\n");
			if (cmd)
				exit_status = execute_command(cmd);
			free_cmd(cmd);
		}
		free(input);
	}
	return (exit_status);
}

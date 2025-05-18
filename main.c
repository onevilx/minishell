/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onevil_x <onevil_x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:30:28 by obouftou          #+#    #+#             */
/*   Updated: 2025/05/18 03:10:55 by onevil_x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/protos.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_cmd	*cmd;

	(void)argc;
	(void)argv;
	init_env(envp);
	ft_launching();
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			sigterm_handler(0);
		if (*input)
		{
			add_history(input);
			cmd = ft_input_proces(input);
			printf("------------------------------------------\n");
			if (cmd)
				execute_command(cmd);
			free_cmd(cmd);
		}
		free(input);
	}
	return (0);
}

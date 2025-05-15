/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:30:28 by obouftou          #+#    #+#             */
/*   Updated: 2025/05/15 16:08:25 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/protos.h"

int main(int argc, char **argv, char **envp)
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
			cmd = ft_input_proces(input); // parser o kolchi so cmd atkon m9adda
			printf("------------------------------------------\n");
			if (cmd->red)
				handle_redirections(cmd);
			if (!execute_builtin(cmd))
			{
				if (!execute_external(cmd))
					printf("minishell: command not found: %s\n", cmd->args ? cmd->args->value : "NULL");
			}
			free_cmd(cmd);
		}
		free(input);
	}
	return (0);
}

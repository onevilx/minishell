/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:30:28 by obouftou          #+#    #+#             */
/*   Updated: 2025/04/27 18:10:22 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/protos.h"

static void	free_args(char **args)
{
	int i;

	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_cmd	*cmd;
	char	**args;

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
		// hna khsna nlinkiw lkhdma binatna
		args = ft_split(input, ' ');// execute part
			if (!execute_builtin(args))
			{
				if (!execute_external(args))
				printf("minishell: command not found: %s\n", args[0]);
			}
			free_args(args);
		}
		free(input);
	}
	return (0);
}

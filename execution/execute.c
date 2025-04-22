/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:30:55 by yaboukir          #+#    #+#             */
/*   Updated: 2025/04/22 16:05:20 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniheader.h"

// Converts t_token list into a NULL-terminated array
char **token_to_args(t_token *token)
{
	int i = 0;
	t_token *tmp = token;
	char **args;

	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}

	args = malloc(sizeof(char *) * (i + 1));
	if (!args)
		return NULL;

	i = 0;
	while (token)
	{
		args[i++] = token->value;
		token = token->next;
	}
	args[i] = NULL;

	return args;
}

void execute_cmd(t_cmd *cmd, char **envp)
{
	pid_t pid;
	char **args;
    
	if (!cmd || !cmd->token)
		return;

	args = token_to_args(cmd->token);
	if (!args || !args[0])
		return;

	pid = fork();
	if (pid == 0)
	{
		execvp(args[0], args); // using execvp for simplicity
		perror("execvp");
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, NULL, 0);
}

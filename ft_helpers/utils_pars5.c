/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouftou <obouftou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:40:16 by obouftou          #+#    #+#             */
/*   Updated: 2025/06/24 16:39:38 by obouftou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

bool	handle_too_many_heredocs(t_token *cur, int *exit_status)
{
	if (count_heredoc(cur) > 16)
	{
		write(2, "minishell: too many heredocs (max 16)\n", 39);
		*exit_status = 2;
		exit(2);
	}
	return (true);
}

bool	is_redirection_without_target(t_token *cur, int *exit_status)
{
	t_token	*next;

	next = cur->next;
	if (!next || next->type != WORD)
	{
		printf("syntax error near unexpected token `newline'\n");
		*exit_status = 258;
		return (false);
	}
	return (true);
}

bool	process_heredoc_redirection(t_token *cur, int *exit_status, int *index)
{
	t_env	*env;
	char	*content;
	char	*filename;
	t_token	*next;

	next = cur->next;
	signal(SIGINT, heredoc_sig);
	env = ft_init_env_list(*get_env());
	content = read_input(next->value, env, next->quote_type, *exit_status);
	if (!content || g_signal == 1)
		return (false);
	filename = generate_tmp_filename((*index)++);
	if (!filename || write_heredoc_tmp(filename, content) == -1)
	{
		free(filename);
		free(content);
		return (false);
	}
	free(content);
	free(next->value);
	next->value = filename;
	cur->type = REDIR_IN;
	signal(SIGINT, sigint_handler);
	return (true);
}

bool	handle_redirection(t_token *cur, int *exit_status, int *heredoc_idx)
{
	if (!is_redirection_without_target(cur, exit_status))
		return (false);
	if (cur->type == HEREDOC)
	{
		if (!process_heredoc_redirection(cur, exit_status, heredoc_idx))
			return (false);
	}
	return (true);
}

void	heredoc_sig(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = 1;
		close(STDIN_FILENO);
	}
}

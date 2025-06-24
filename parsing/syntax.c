/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouftou <obouftou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:50:10 by obouftou          #+#    #+#             */
/*   Updated: 2025/06/24 15:44:13 by obouftou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

static bool	check_semicolon(t_token *token, int *exit_status)
{
	while (token)
	{
		if (token->quote_type == '\0')
		{
			if (token->type == WORD && strchr(token->value, ';'))
			{
				*exit_status = 258;
				printf("minishell: syntax error near unexpected token `;'\n");
				return (false);
			}
		}
		token = token->next;
	}
	return (true);
}

static bool	check_start_token(t_token *token, int *exit_status)
{
	if (token->type == PIPE)
	{
		printf("Syntax error: unexpected token '%s'\n", token->value);
		*exit_status = 258;
		return (false);
	}
	return (true);
}

static bool	check_pipe_sequence(t_token *cur, int *exit_status)
{
	if (cur->type == PIPE)
	{
		if (!cur->next || cur->next->type == PIPE)
		{
			printf("Syntax error: unexpected token after '|'\n");
			*exit_status = 258;
			return (false);
		}
	}
	return (true);
}

bool	check_redirections(t_token *cur, int *exit_status)
{
	static int	heredoc_index = 0;

	g_signal = 0;
	if (!handle_too_many_heredocs(cur, exit_status))
		return (false);
	if (cur->type == REDIR_IN || cur->type == REDIR_OUT
		|| cur->type == APPEND || cur->type == HEREDOC)
	{
		if (!handle_redirection(cur, exit_status, &heredoc_index))
			return (false);
	}
	return (true);
}

bool	syntax_check(t_token *token, int *exit_status)
{
	t_token	*cur;

	cur = token;
	if (!cur)
		return (false);
	if (!check_semicolon(token, exit_status)
		|| !check_start_token(token, exit_status))
		return (false);
	while (cur)
	{
		if (!check_pipe_sequence(cur, exit_status)
			|| !check_redirections(cur, exit_status))
			return (false);
		cur = cur->next;
	}
	return (true);
}

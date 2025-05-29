/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouftou <obouftou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:50:10 by obouftou          #+#    #+#             */
/*   Updated: 2025/05/29 15:56:59 by obouftou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

static bool	check_semicolon(t_token *token)
{
	while (token)
	{
		if (token->type == WORD && strchr(token->value, ';'))
		{
			printf("minishell: syntax error near unexpected token `;'\n");
			return (false);
		}
		token = token->next;
	}
	return (true);
}

static bool	check_start_token(t_token *token)
{
	if (token->type == PIPE)
	{
		printf("Syntax error: unexpected token '%s'\n", token->value);
		return (false);
	}
	return (true);
}


static bool	check_pipe_sequence(t_token *cur)
{
	if (cur->type == PIPE)
	{
		if (!cur->next || cur->next->type == PIPE)
		{
			printf("Syntax error: unexpected token after '|'\n");
			return (false);
		}
	}
	return (true);
}

static bool	check_redirections(t_token *cur)
{
	t_token	*next;

	if (cur->type == REDIR_IN || cur->type == REDIR_OUT
		|| cur->type == APPEND || cur->type == HEREDOC)
	{
		next = cur->next;
		if (!next || next->type != WORD)
		{
			printf("Syntax error: redirection without target\n");
			return (false);
		}
	}
	if (!cur->next && (cur->type == PIPE || cur->type == REDIR_IN
			|| cur->type == REDIR_OUT
			|| cur->type == APPEND || cur->type == HEREDOC))
	{
		printf("Syntax error: unexpected end after '%s'\n", cur->value);
		return (false);
	}
	return (true);
}


bool	syntax_check(t_token *token)
{
	t_token	*cur;

	cur = token;
	if (!cur)
		return (false);
	if (!check_semicolon(token) || !check_start_token(token))
		return (false);
	while (cur)
	{
		if (!check_pipe_sequence(cur) || !check_redirections(cur))
			return (false);
		cur = cur->next;
	}
	return (true);
}

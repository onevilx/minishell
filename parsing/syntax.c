/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouftou <obouftou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:50:10 by obouftou          #+#    #+#             */
/*   Updated: 2025/06/18 19:45:37 by obouftou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

static bool	check_semicolon(t_token *token)
{
	while (token)
	{
		if (token->quote_type == '\0')
		{

			if (token->type == WORD && strchr(token->value, ';'))
			{
				printf("minishell: syntax error near unexpected token `;'\n");
				return (false);
			}
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
	t_env	*env;
	char	*filename;
	char	*content;
	static int	heredoc_index = 0;

	if (cur->type == REDIR_IN || cur->type == REDIR_OUT
		|| cur->type == APPEND || cur->type == HEREDOC)
	{
		next = cur->next;
		if (!next || next->type != WORD)
		{
			printf("Syntax error: redirection without target\n");
			return (false);
		}
		if (cur->type == HEREDOC)
		{
			env = ft_init_env_list(*get_env());
			content = read_input(next->value, env, next->quote_type ,0);
			if (!content)
				return (false);
			filename = generate_tmp_filename(heredoc_index++);
			if (!filename || write_heredoc_tmp(filename, content) == -1)
			{
				free(filename);
				free(content);
				return (false);
			}
			free(content);
			free(next->value);
			next->value = filename;
			cur->type = REDIR_IN; // convert HEREDOC to normal redirection
		}
	}
	if (!cur->next && (cur->type == PIPE || cur->type == REDIR_IN
			|| cur->type == REDIR_OUT || cur->type == APPEND || cur->type == HEREDOC))
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

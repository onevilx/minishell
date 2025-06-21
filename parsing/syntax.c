/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:50:10 by obouftou          #+#    #+#             */
/*   Updated: 2025/06/21 23:13:17 by yaboukir         ###   ########.fr       */
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
			*exit_status = 10000;
			return (false);
		}
	}
	return (true);
}

void heredoc_sig(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = 1;
		close(STDIN_FILENO);
	}
}

static bool	check_redirections(t_token *cur, int *exit_status)
{
	t_token	*next;
	t_env	*env;
	char	*filename;
	char	*content;
	static int	heredoc_index = 0;
	int exit_code;
	g_signal = 0;
	exit_code = *exit_status;
	if (cur->type == REDIR_IN || cur->type == REDIR_OUT
		|| cur->type == APPEND || cur->type == HEREDOC)
	{
		next = cur->next;
		if (!next || next->type != WORD)
		{
			printf("Syntax error: redirection without target\n");
			*exit_status = 1000;
			return (false);
		}
		if (cur->type == HEREDOC)
		{
			signal(SIGINT, heredoc_sig);
			env = ft_init_env_list(*get_env());
			content = read_input(next->value, env, next->quote_type ,exit_code);
			if (!content || g_signal == 1)
			{
				// update exit status if heredoc was interrupted
				return (false);
			}
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
			signal(SIGINT, sigint_handler);
		}
	}
	if (!cur->next && (cur->type == PIPE || cur->type == REDIR_IN
			|| cur->type == REDIR_OUT || cur->type == APPEND || cur->type == HEREDOC))
	{
		printf("Syntax error: unexpected end after '%s'\n", cur->value);
		*exit_status = 44;
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
	if (!check_semicolon(token, exit_status) || !check_start_token(token, exit_status))
		return (false);
	while (cur)
	{
		if (!check_pipe_sequence(cur, exit_status) || !check_redirections(cur, exit_status))
			return (false);
		cur = cur->next;
	}
	return (true);
}

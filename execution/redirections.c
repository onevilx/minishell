/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:00:59 by yaboukir          #+#    #+#             */
/*   Updated: 2025/05/16 00:54:07 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

static int	redirect_out(t_token *token)
{
	int	fd;

	fd = open(token->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open (output redir)");
		return (0);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

static int	redirect_in(t_token *token)
{
	int	fd;

	fd = open(token->next->value, O_RDONLY);
	if (fd == -1)
	{
		perror("open (input redir)");
		return (0);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (1);
}

void	handle_redirections(t_cmd *cmd)
{
	t_token	*curr;

	curr = *(cmd->token);
	while (curr)
	{
		if (curr->type == REDIR_OUT && curr->next)
		{
			if (!redirect_out(curr))
				return ;
			curr = curr->next;
		}
		else if (curr->type == REDIR_IN && curr->next)
		{
			if (!redirect_in(curr))
				return ;
			curr = curr->next;
		}
		curr = curr->next;
	}
}

void	handle_append(t_cmd *cmd)
{
	t_token	*curr;

	curr = *(cmd->token);
	while (curr)
	{
		if (curr->type == APPEND)
		{
			if (!do_append_redirection(curr))
				return ;
			curr = curr->next;
		}
		curr = curr->next;
	}
}

void	handle_heredoc(t_cmd *cmd)
{
	t_redirect	*redir;
	char		*content;

	redir = cmd->red;
	while (redir)
	{
		if (redir->type == HEREDOC)
		{
			content = read_input(redir->val);
			if (!content || write_heredoc_tmp(content) == -1)
				return (free(content), (void)0);
			free(content);
			if (read_heredoc_tmp() == -1)
				return ;
		}
		redir = redir->next;
		unlink(".heredoc_tmp");
	}
}

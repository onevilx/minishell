/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:00:59 by yaboukir          #+#    #+#             */
/*   Updated: 2025/06/21 23:07:36 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

static int	handle_redir_in(t_redirect *redir)
{
	int	fd = open(redir->val, O_RDONLY);
	if (fd == -1)
	{
		perror("open (REDIR_IN)");
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	handle_redir_out(t_redirect *redir)
{
	int	fd = open(redir->val, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open (REDIR_OUT)");
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	handle_redirections(t_cmd *cmd)
{
	t_redirect	*redir;

	redir = cmd->red;
	while (redir)
	{
		if (redir->type == REDIR_IN)
		{
			if (handle_redir_in(redir) == -1)
				return (0);
		}
		else if (redir->type == REDIR_OUT)
		{
			if (handle_redir_out(redir) == -1)
				return (0);
		}
		redir = redir->next;
	}
	return (1);
}

int	handle_append(t_cmd *cmd)
{
	t_token	*curr;

	curr = *(cmd->token);
	while (curr)
	{
		if (curr->type == APPEND)
		{
			if (!do_append_redirection(curr))
				return (0);
		}
		curr = curr->next;
	}
	return (1);
}

int	handle_heredoc(t_cmd *cmd)
{
	t_redirect	*redir;
	// int			index;

	// index = 0;
	redir = cmd->red;
	while (redir)
	{
		if (redir->type == HEREDOC)
		{
			// if (!process_heredoc(redir, index++))
				return (0);
		}
		redir = redir->next;
	}
	return (1);
}

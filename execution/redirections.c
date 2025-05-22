/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:00:59 by yaboukir          #+#    #+#             */
/*   Updated: 2025/05/22 19:43:42 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

int	handle_redirections(t_cmd *cmd)
{
	t_redirect	*redir;
	int			fd;

	redir = cmd->red;
	while (redir)
	{
		if (redir->type == REDIR_IN)
		{
			fd = open(redir->val, O_RDONLY);
			if (fd == -1)
			{
				perror("open (REDIR_IN)");
				return (0);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (redir->type == REDIR_OUT)
		{
			fd = open(redir->val, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd == -1)
			{
				perror("open (REDIR_OUT)");
				return (0);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		redir = redir->next;
	}
	return (1);
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
	char		*filename;
	char		*content;
	int			i;

	i = 0;
	redir = cmd->red;
	while (redir)
	{
		if (redir->type == HEREDOC)
		{
			content = read_input(redir->val);
			filename = ft_strjoin(".heredoc_", ft_itoa(i++));
			if (!content || write_heredoc_tmp(filename, content) == -1)
			{
				free(filename);
				free(content);
				return ;
			}
			free(content);
			free(redir->val);
			redir->val = filename;
			redir->type = REDIR_IN;
		}
		redir = redir->next;
	}
}

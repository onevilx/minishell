/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:00:59 by yaboukir          #+#    #+#             */
/*   Updated: 2025/04/22 23:38:03 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

void	handle_redirections(t_token **tokens)
{
	int i;
	int fd;

	i = -1;
	while (tokens[++i] != NULL)
	{
		if (tokens[i]->type == REDIR_IN)
		{
			fd = open(tokens[i + 1]->value, O_RDONLY);
			if (fd == -1)
				perror("Error opening file for input redirection");
			else
				dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (tokens[i]->type == REDIR_OUT)
		{
			fd = open(tokens[i + 1]->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				perror("Error opening file for output redirection");
			else
				dup2(fd, STDOUT_FILENO);
			close(fd);
		}
	}
}

void	handle_APPEND(t_token **tokens)
{
	int i;
	int fd;

	i = 0;
	while (tokens[i] != NULL)
	{
		if (tokens[i]->type == APPEND)
		{
			fd = open(tokens[i + 1]->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				perror("Error opening file for append redirection");
			else
				dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		i++;
	}
}

void	handle_heredoc(t_token **tokens)
{
	int		fd;
	char	*delimiter;
	int		i;

	i = 0;
	while (tokens[i] && tokens[i]->type != HEREDOC)
		i++;
	if (!tokens[i])
		return ;
	delimiter = tokens[i + 1]->value;
	fd = open_tmpfile();
	if (fd == -1)
		return ;
	read_input(fd, delimiter);
	close(fd);
	fd = open("/tmp/heredoc_input.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening temporary file for heredoc");
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	unlink("/tmp/heredoc_input.txt");
}

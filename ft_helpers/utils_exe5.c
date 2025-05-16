/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 00:28:52 by yaboukir          #+#    #+#             */
/*   Updated: 2025/05/16 01:01:47 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

t_arg	*char_array_to_args_list(char **array)
{
	int		i;
	t_arg	*new;
	t_arg	*head;
	t_arg	*current;

	i = 0;
	head = NULL;
	current = NULL;
	while (array && array[i])
	{
		new = malloc(sizeof(t_arg));
		if (!new)
			return (NULL);
		new->value = array[i];
		new->next = NULL;
		if (!head)
			head = new;
		else
			current->next = new;
		current = new;
		i++;
	}
	return (head);
}

void	sanitize_args(t_cmd *cmd)
{
	int		i;
	char	**args;
	t_token	*tok;

	i = 0;
	tok = *(cmd->token);
	args = malloc(sizeof(char *) * 100);
	while (tok)
	{
		if (tok->type == REDIR_IN || tok->type == REDIR_OUT
			|| tok->type == APPEND || tok->type == HEREDOC)
		{
			tok = tok->next;
			if (tok)
				tok = tok->next;
		}
		else
		{
			args[i++] = tok->value;
			tok = tok->next;
		}
	}
	args[i] = NULL;
	cmd->args = char_array_to_args_list(args);
}

void	remove_heredoc_tokens(t_cmd *cmd)
{
	int		i;
	int		j;
	t_token	**tokens;

	i = 0;
	tokens = cmd->token;
	while (tokens[i])
	{
		if (tokens[i]->type == HEREDOC)
		{
			free(tokens[i]);
			free(tokens[i + 1]);
			j = i;
			while (tokens[j + 2])
			{
				tokens[j] = tokens[j + 2];
				j++;
			}
			tokens[j] = NULL;
			tokens[j + 1] = NULL;
		}
		else
			i++;
	}
}

int	write_heredoc_tmp(char *content)
{
	int	fd;

	fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("minishell: open heredoc tmp file");
		return (-1);
	}
	write(fd, content, ft_strlen(content));
	close(fd);
	return (0);
}

int	read_heredoc_tmp(void)
{
	int	fd;

	fd = open(".heredoc_tmp", O_RDONLY);
	if (fd == -1)
	{
		perror("minishell: open heredoc tmp file for reading");
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

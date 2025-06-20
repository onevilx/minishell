/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouftou <obouftou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 00:28:52 by yaboukir          #+#    #+#             */
/*   Updated: 2025/06/20 17:59:47 by obouftou         ###   ########.fr       */
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
		new = g_malloc(sizeof(t_arg));
		if (!new)
			return (NULL);
		new->value = ft_strdup(array[i]);
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

int	sanitize_args(t_cmd *cmd)
{
	char	**args;
	t_token	*tok;

	tok = *(cmd->token);
	args = extract_args(tok);
	if (!args)
		return (0);
	if (!handling_cmdops(cmd))
	{
		*get_exit_status() = 1;
		return (0);
	}
	cmd->args = char_array_to_args_list(args);
	ft_free_split(args);
	return (1);
}

void	cleanup_cmdops_files(t_cmd *cmd)
{
	t_redirect	*redir;

	redir = cmd->red;
	while (redir)
	{
		if (redir->type == REDIR_IN && redir->val
			&& ft_strncmp(redir->val, "/tmp/.heredoc_", 9) == 0)
			unlink(redir->val);
		redir = redir->next;
	}
}

int	write_heredoc_tmp(char *filename, char *content)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("heredoc write"), -1);
	write(fd, content, ft_strlen(content));
	close(fd);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe10.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onevil_x <onevil_x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 19:44:17 by yaboukir          #+#    #+#             */
/*   Updated: 2025/06/05 01:17:01 by onevil_x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

void	handle_export_logic(t_arg *arg, char *key, int append, int pos)
{
	int		idx;
	char	**env;

	env = *get_env();
	idx = find_env_index(env, key);
	if (append)
		append_to_env(key, ft_strdup(arg->value + pos + 2), idx);
	else if (arg->value[pos] == '=')
	{
		if (idx >= 0)
			update_env_var(idx, arg->value);
		else
			add_env_var(arg->value);
	}
}

char	*generate_tmp_filename(int index)
{
	char	*index_str;
	char	*filename;

	index_str = ft_itoa(index);
	if (!index_str)
		return (NULL);
	filename = ft_strjoin("/tmp/.heredoc_", index_str);
	free(index_str);
	return (filename);
}

int	count_heredocs(t_cmd *cmd)
{
	t_cmd *cur = cmd;
	t_redirect *redir;
	int count = 0;

	while (cur)
	{
		redir = cur->red;
		while (redir)
		{
			if (redir->type == HEREDOC)
				count++;
			redir = redir->next;
		}
		cur = cur->next;
	}
	return (count);
}

int	process_heredoc(t_redirect *redir, int index)
{
	char	*content;
	char	*filename;

	content = read_input(redir->val);
	filename = generate_tmp_filename(index);
	if (!content || !filename || write_heredoc_tmp(filename, content) == -1)
	{
		free(content);
		free(filename);
		return (0);
	}
	free(content);
	free(redir->val);
	redir->val = filename;
	redir->type = REDIR_IN;
	return (1);
}

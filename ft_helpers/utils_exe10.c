/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe10.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 19:44:17 by yaboukir          #+#    #+#             */
/*   Updated: 2025/06/25 00:37:37 by yaboukir         ###   ########.fr       */
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

int	count_heredoc(t_token *token)
{
	t_token	*cur;
	int		count;

	count = 0;
	cur = token;
	while (cur)
	{
		if (cur->type == HEREDOC)
			count++;
		cur = cur->next;
	}
	return (count);
}

int	is_digit_str(const char *str, int i, int sign)
{
	unsigned long long	result;

	result = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		result = result * 10 + (str[i] - '0');
		if ((sign == 1 && result > LLONG_MAX)
			|| (sign == -1 && result > (unsigned long long)LLONG_MAX + 1))
			return (0);
		i++;
	}
	return (1);
}

void	exec_direct_path(t_cmd *cmd, char **args_array)
{
	if (access(cmd->args->value, F_OK) == 0)
	{
		if (is_directory(cmd->args->value))
		{
			errno = EISDIR;
			perror(cmd->args->value);
			exit(126);
		}
		if (access(cmd->args->value, X_OK) == 0)
			execve(cmd->args->value, args_array, *get_env());
		else
		{
			errno = EACCES;
			perror(cmd->args->value);
			exit(126);
		}
	}
	errno = ENOENT;
	perror(cmd->args->value);
	exit(127);
}

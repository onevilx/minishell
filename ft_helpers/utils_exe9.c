/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe9.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:41:05 by yaboukir          #+#    #+#             */
/*   Updated: 2025/05/20 18:50:21 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

char	**args_to_array(t_arg *args)
{
	t_arg	*current;
	int		count;
	char	**arr;
	int		i;

	count = 0;
	current = args;
	while (current)
	{
		count++;
		current = current->next;
	}
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	current = args;
	i = 0;
	while (current)
	{
		arr[i] = ft_strdup(current->value);
		current = current->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

// Try executing the command using paths in $PATH
void	try_exec_paths(t_cmd *cmd)
{
	char	**paths;
	char	*path;
	int		i;
	char	**args_array;

	paths = ft_split(getenv("PATH"), ':');
	if (!paths)
		exit(1);
	args_array = args_to_array(cmd->args);
	if (!args_array)
		exit(1);
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin_free(path, args_array[0]);
		if (access(path, X_OK) == 0)
			execve(path, args_array, *get_env());
		free(path);
		i++;
	}
	free_split(paths);
	printf("minishell: command not found: %s\n", args_array[0]);
	free(args_array);
	exit(127);
}

t_arg	*token_to_args(t_token *start, t_token *end)
{
	t_arg	*head;
	t_arg	*tail;
	t_arg	*new_arg;

	head = NULL;
	tail = NULL;
	while (start && start != end)
	{
		if (start->type == WORD)
		{
			new_arg = malloc(sizeof(t_arg));
			if (!new_arg)
				return (NULL);
			new_arg->value = ft_strdup(start->value);
			new_arg->next = NULL;
			if (!head)
				head = new_arg;
			else
				tail->next = new_arg;
			tail = new_arg;
		}
		start = start->next;
	}
	return (head);
}

char	**extract_args(t_token *tok)
{
	char	**args;
	int		i;

	args = malloc(sizeof(char *) * 100);
	if (!args)
		return (NULL);
	i = 0;
	while (tok)
	{
		if (is_redirection(tok))
		{
			tok = tok->next;
			if (tok)
				tok = tok->next;
		}
		else if (tok->type == PIPE)
			break ;
		else
		{
			args[i++] = tok->value;
			tok = tok->next;
		}
	}
	args[i] = NULL;
	return (args);
}

void	sanitize_all_args(t_cmd *cmd)
{
	t_cmd	*cur;

	cur = cmd;
	while (cur)
	{
		sanitize_args(cur);
		cur = cur->next;
	}
}

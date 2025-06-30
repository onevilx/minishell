/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe9.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:41:05 by yaboukir          #+#    #+#             */
/*   Updated: 2025/06/30 23:22:22 by yaboukir         ###   ########.fr       */
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
	arr = g_malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (free(arr), NULL);
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

void	try_exec_paths(t_cmd *cmd)
{
	char	**paths;
	char	**args_array;

	args_array = args_to_array(cmd->args);
	if (!args_array)
		exit(1);
	paths = get_paths_array();
	try_exec_in_paths(paths, args_array, *get_env());
	if (paths != NULL && paths != (char *[]){"/bin", "/usr/bin", NULL})
		printf("minishell: command not found: %s\n", args_array[0]);
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
			new_arg = g_malloc(sizeof(t_arg));
			if (!new_arg)
				return (NULL);
			new_arg->value = ft_strdup(start->value);
			new_arg->quote_type = start->quote_type;
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

	args = g_malloc(sizeof(char *) * 100);
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

int	sanitize_all_args(t_cmd *cmd)
{
	t_cmd	*cur;
	int		ret;

	cur = cmd;
	if (cmd && cmd->args && ft_strcmp(cmd->args->value,
			"exit") == 0 && cmd->next == NULL)
	{
		ret = builtin_exit(cmd->args, 1);
		if (ret != 1)
			exit(ret);
		return (0);
	}
	while (cur)
	{
		if (!sanitize_args(cur))
			return (0);
		cur = cur->next;
	}
	return (1);
}

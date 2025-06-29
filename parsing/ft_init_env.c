/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouftou <obouftou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:50:50 by yaboukir          #+#    #+#             */
/*   Updated: 2025/06/29 17:54:50 by obouftou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

t_env	*ft_lstnew(void *key, char *value)
{
	t_env	*new;

	new = g_malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

static t_env	*add_to_env_list(char *str1)
{
	char	**splited;
	t_env	*node;

	splited = ft_split_once(str1, '=');
	if (!splited || !splited[0] || !splited[1])
		return (NULL);
	node = ft_lstnew(ft_strdup(splited[0]), ft_strdup(splited[1]));
	free(splited[0]);
	free(splited[1]);
	free(splited);
	return (node);
}

t_env	*ft_init_env_list(char **env)
{
	int		i;
	t_env	*head;
	t_env	*last;
	t_env	*new;

	i = 0;
	head = NULL;
	last = NULL;
	while (env[i])
	{
		new = add_to_env_list(env[i]);
		if (!head)
			head = new;
		else
		{
			last->next = new;
			new->prev = last;
		}
		last = new;
		i++;
	}
	return (head);
}

void	print_ambiguous_error(const char *val)
{
	write(2, "minishell: ", 11);
	if (val)
		write(2, val, ft_strlen(val));
	write(2, ": ambiguous redirect\n", 22);
}

bool	check_ambg(t_token *tokens, int *exit_status)
{
	t_token	*cur;
	t_token	*target;

	cur = tokens;
	while (cur)
	{
		if ((cur->type == REDIR_OUT || cur->type == REDIR_IN
				|| cur->type == APPEND || cur->type == HEREDOC)
			&& cur->next && cur->next->type == WORD)
		{
			target = cur->next;
			if (is_ambiguous_target(target))
			{
				handle_ambiguous(cur, target, exit_status);
				return (true);
			}
		}
		cur = cur->next;
	}
	return (true);
}

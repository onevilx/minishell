/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:50:50 by yaboukir          #+#    #+#             */
/*   Updated: 2025/06/21 16:03:36 by yaboukir         ###   ########.fr       */
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

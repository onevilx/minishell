/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouftou <obouftou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:54:42 by obouftou          #+#    #+#             */
/*   Updated: 2025/06/27 00:13:27 by obouftou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

t_redirect	*add_redirect(t_redirect *head, t_code type, char *val)
{
	t_redirect	*new;
	t_redirect	*cur;

	new = g_malloc(sizeof(t_redirect));
	if (!new)
		return (NULL);
	new->type = type;
	new->val = val;
	new->next = NULL;
	if (!head)
		return (new);
	cur = head;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
	return (head);
}

int	count_pipes(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens)
	{
		if (tokens->type == PIPE)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

void	free_command_list(t_cmd *head)
{
	t_cmd	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->token);
		free(tmp);
	}
}

void	init_for_norm(t_cmd	**head, t_cmd **last,
		int *total_pipes, t_token *tokens)
{
	*head = NULL;
	*last = NULL;
	*total_pipes = count_pipes(tokens);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouftou <obouftou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:54:42 by obouftou          #+#    #+#             */
/*   Updated: 2025/05/07 17:54:52 by obouftou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

t_redirect	*add_redirect(t_redirect *head, t_code type, char *val)
{
	t_redirect *new;

	new = malloc(sizeof(t_redirect));
	if (!new)
		return (NULL);
	new->type = type;
	new->val = val;
	new->next = NULL;
	if (!head)
		return (new);
	t_redirect *cur = head;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
	return (head);
}

int count_pipes(t_token *tokens)
{
	int count = 0;
	while (tokens)
	{
		if (tokens->type == PIPE)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

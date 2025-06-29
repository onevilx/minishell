/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_empty.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouftou <obouftou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:25:48 by obouftou          #+#    #+#             */
/*   Updated: 2025/06/29 17:54:12 by obouftou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

bool	is_ambiguous_target(t_token *target)
{
	return (!target->value || target->value[0] == '\0'
		|| ft_strchr(target->value, ' '));
}

void	handle_ambiguous(t_token *cur, t_token *target, int *exit_status)
{
	print_ambiguous_error(target->value);
	*exit_status = 1;
	target->not_hide = false;
	cur->type = WORD;
	free(cur->value);
	cur->value = ft_strdup("");
}

void	ft_remove_empty(t_token **tokens)
{
	t_token	*cur;
	t_token	*prev;
	t_token	*next;

	prev = NULL;
	cur = *tokens;
	while (cur)
	{
		next = cur->next;
		if (cur->type == WORD
			&& (!cur->value || cur->value[0] == '\0') && !cur->not_hide)
		{
			if (!prev)
				*tokens = next;
			else
				prev->next = next;
			free(cur->value);
			free(cur);
			cur = next;
			continue ;
		}
		prev = cur;
		cur = next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_empty.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouftou <obouftou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:25:48 by obouftou          #+#    #+#             */
/*   Updated: 2025/06/24 15:43:16 by obouftou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

void	ft_remove_empty(t_token **tokens)
{
	t_token	*cur = *tokens;
	t_token	*prev = NULL;
	t_token	*next;

	while (cur)
	{
		next = cur->next;
		if (cur->type == WORD && (!cur->value || cur->value[0] == '\0') && !cur->not_hide)
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



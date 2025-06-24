/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars10.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouftou <obouftou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:43:34 by obouftou          #+#    #+#             */
/*   Updated: 2025/06/24 20:51:54 by obouftou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

void	merge_tokens(t_token *head)
{
	t_token	*cur;
	t_token	*next;
	char	*joined;

	cur = head;
	while (cur && cur->next)
	{
		next = cur->next;
		if (cur->type == WORD && next->type == WORD
			&& !cur->space_after && (cur->quote_type == '\''
				|| cur->quote_type == '"'))
		{
			joined = ft_strjoin(cur->value, next->value);
			free(cur->value);
			cur->value = joined;
			cur->space_after = next->space_after;
			cur->next = next->next;
			free(next->value);
			free(next);
			continue ;
		}
		cur = cur->next;
	}
}

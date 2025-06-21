/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_empty.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouftou <obouftou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:25:48 by obouftou          #+#    #+#             */
/*   Updated: 2025/06/21 17:58:24 by obouftou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

/*
i have an essue when finishing the expanding phase and founding
some unvailable variables in the evirement i store empty tokens 
who creats some errors i need to filter my tokens and verbose/delete them befor 
execution phase im thinking of adding a function that cheks the tokens by looping over them 
values and remove if an empty token appears ft_remove_empty(t_token *tokens)
*/

void	ft_remove_empty(t_token **tokens)
{
	t_token	*cur;
	t_token	*prev;
	t_token	*tmp;

	while (*tokens && (*tokens)->value && (*tokens)->value[0] == '\0')
	{
		tmp = *tokens;
		*tokens = (*tokens)->next;
		free(tmp->value);
		free(tmp);
	}

	prev = *tokens;
	if (!prev)
		return;
	cur = prev->next;
	while (cur)
	{
		if (cur->value && cur->value[0] == '\0')
		{
			tmp = cur;
			prev->next = cur->next;
			free(tmp->value);
			free(tmp);
			cur = prev->next;
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
}


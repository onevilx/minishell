/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_empty.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouftou <obouftou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:25:48 by obouftou          #+#    #+#             */
/*   Updated: 2025/06/21 20:53:43 by obouftou         ###   ########.fr       */
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
	t_token	*cur = *tokens;
	t_token	*prev = NULL;
	t_token	*next;

	while (cur)
	{
		next = cur->next;
		if (cur->type == WORD && (!cur->value || cur->value[0] == '\0'))
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



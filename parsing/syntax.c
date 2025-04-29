/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouftou <obouftou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:50:10 by obouftou          #+#    #+#             */
/*   Updated: 2025/04/29 18:30:50 by obouftou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

bool	syntax_check(t_token *token)
{
	t_token *cur = token;

	if (!cur)
		return false;
	if (cur->type == PIPE || cur->type == REDIR_IN ||
		cur->type == REDIR_OUT || cur->type == APPEND || cur->type == HEREDOC)
	{
		printf("Syntax error: unexpected token '%s'\n", cur->value);
		return false;
	}
	while (cur)
	{
		if (cur->type == PIPE)
		{
			if (!cur->next || cur->next->type == PIPE)
			{
				printf("Syntax error: unexpected token after '|'\n");
				return false;
			}
		}
		if (cur->type == REDIR_IN || cur->type == REDIR_OUT ||
			cur->type == APPEND || cur->type == HEREDOC)
		{
			if (!cur->next || cur->next->type != WORD)
			{
				printf("Syntax error: redirection without target\n");
				return false;
			}
		}
		if (!cur->next && (cur->type == PIPE || cur->type == REDIR_IN ||
			cur->type == REDIR_OUT || cur->type == APPEND || cur->type == HEREDOC))
		{
			printf("Syntax error: unexpected end after '%s'\n", cur->value);
			return false;
		}

		cur = cur->next;
	}
	return true;
}

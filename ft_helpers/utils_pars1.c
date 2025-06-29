/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouftou <obouftou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:03:35 by obouftou          #+#    #+#             */
/*   Updated: 2025/06/29 17:38:58 by obouftou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

bool	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

t_token	*new_token(t_code type, char *val, char quote_type)
{
	t_token	*tok;

	tok = g_malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->type = type;
	tok->not_hide = false;
	tok->value = val;
	tok->quote_type = quote_type;
	tok->next = NULL;
	return (tok);
}

void	add_token(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_token	*parse_operator(const char *input, int *i)
{
	if (input[*i] == '>' && input[*i + 1] == '>')
	{
		*i += 2;
		return (new_token(APPEND, strdup(">>"), '\0'));
	}
	if (input[*i] == '<' && input[*i + 1] == '<')
	{
		*i += 2;
		return (new_token(HEREDOC, strdup("<<"), '\0'));
	}
	if (input[*i] == '>')
		return (new_token(REDIR_OUT, ft_strndup(&input[(*i)++], 1), '\0'));
	if (input[*i] == '<')
		return (new_token(REDIR_IN, ft_strndup(&input[(*i)++], 1), '\0'));
	if (input[*i] == '|')
		return (new_token(PIPE, ft_strndup(&input[(*i)++], 1), '\0'));
	return (NULL);
}

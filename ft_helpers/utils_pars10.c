/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars10.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouftou <obouftou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:43:34 by obouftou          #+#    #+#             */
/*   Updated: 2025/06/25 00:08:53 by obouftou         ###   ########.fr       */
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

static int	count_leading_dollars(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == '$')
		i++;
	return (i);
}

static void	update_token_value(t_token *tok, int dollar_count)
{
	char	*rest;
	char	*new_val;

	rest = ft_strdup(tok->value + dollar_count);
	if (dollar_count % 2 == 1)
		new_val = ft_strjoin("$", rest);
	else
		new_val = ft_strdup(rest);
	free(rest);
	free(tok->value);
	tok->value = new_val;
}

void	normalize_odd_dollars(t_token *tokens)
{
	t_token	*cur;
	int		dollar_count;

	cur = tokens;
	while (cur)
	{
		if (cur->value && cur->value[0] == '$')
		{
			dollar_count = count_leading_dollars(cur->value);
			if (dollar_count > 1)
				update_token_value(cur, dollar_count);
		}
		cur = cur->next;
	}
}

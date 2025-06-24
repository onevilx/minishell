/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars6.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouftou <obouftou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:56:20 by obouftou          #+#    #+#             */
/*   Updated: 2025/06/24 16:38:57 by obouftou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

bool	is_localized_string(t_token *prev)
{
	return (prev && prev->quote_type == '"'
		&& ft_strcmp(prev->value, "$") == 0);
}

char	*handle_dollar(char *input, int *i, t_env *env, int status)
{
	int		start;
	char	*name;

	(*i)++;
	if (input[*i] == '?')
		return (ft_itoa(((*i)++, status)));
	if (!ft_isalpha(input[*i]) && input[*i] != '_')
		return (ft_strdup(""));
	start = *i;
	while (ft_isalnum(input[*i]) || input[*i] == '_')
		(*i)++;
	name = ft_substr(input, start, *i - start);
	return (ft_strdup(get_env_val_list(env, name)));
}

char	*extract_plain(char *input, int *i)
{
	int	start;

	start = *i;
	while (input[*i] && input[*i] != '$')
		(*i)++;
	return (ft_substr(input, start, *i - start));
}

void	replace_token_with_multiple(t_token *old, t_token *new_tokens)
{
	t_token	*next;
	t_token	*first;
	t_token	*last;

	next = old->next;
	first = new_tokens;
	if (!first)
		return ;
	last = first;
	while (last->next)
		last = last->next;
	last->next = next;
	old->type = first->type;
	old->value = first->value;
	old->quote_type = first->quote_type;
	old->space_after = first->space_after;
	old->next = first->next;
}

t_token	*split_expanded_token(char *expanded)
{
	char	**parts;
	t_token	*head;
	t_token	*new;
	int		i;

	i = 0;
	head = NULL;
	parts = ft_split(expanded, ' ');
	while (parts[i])
	{
		new = new_token(WORD, ft_strdup(parts[i]), '\0');
		add_token(&head, new);
		i++;
	}
	return (head);
}

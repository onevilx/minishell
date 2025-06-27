/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars11.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouftou <obouftou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 23:20:47 by obouftou          #+#    #+#             */
/*   Updated: 2025/06/27 01:44:48 by obouftou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

void	handle_export_assignment(t_token *prev, t_token **cur,
				t_env *env, int status)
{
	char	*expanded;
	t_token	*next;

	next = (*cur)->next;
	if (is_unquoted_export_assignment(prev, *cur)
		&& ft_strchr((*cur)->value, '$'))
	{
		expanded = ft_expand_value((*cur)->value, env, status);
		free((*cur)->value);
		(*cur)->value = expanded;
		*cur = next;
	}
}

void	handle_tilde_and_skip(t_token **cur, t_token *prev, t_token *next)
{
	if (is_localized_string(prev) || (*cur)->quote_type == '\'')
	{
		*cur = next;
		return ;
	}
	if (ft_strcmp((*cur)->value, "~") == 0)
	{
		free((*cur)->value);
		(*cur)->value = ft_strdup("$HOME");
	}
}

void	handle_regular_expansion(t_token *cur,
				t_env *env, int status)
{
	if (ft_strchr(cur->value, '$')
		&& (cur->quote_type == '\0' || cur->quote_type == '"'))
		expand_token(cur, env, status);
}

bool	is_unquoted_export_assignment(t_token *prev, t_token *cur)
{
	int i;
	int count;
	
	count = 0;
	i = 0;
	if (!prev || !cur)
		return (false);
	if (prev->type != WORD || ft_strcmp(prev->value, "export") != 0)
		return (false);
	if (cur->quote_type != '\0')
		return (false);
	if (!ft_strchr(cur->value, '='))
		return (false);
	if (cur->value[0] == '=')
		return (false);
	while(cur->value[i])
	{
		if(cur->value[i] == '$')
			count++;
		i++;
	}
	if (count > 1)
		return (false);
	return (true);
}

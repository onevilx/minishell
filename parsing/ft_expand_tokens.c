/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:42:07 by obouftou          #+#    #+#             */
/*   Updated: 2025/06/30 18:26:09 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

char	*get_env_val_list(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return ("");
}

char	*ft_expand_value(char *input, t_env *env, int status)
{
	char	*result;
	char	*tmp;
	int		i;

	i = 0;
	result = ft_strdup("");
	while (input[i])
	{
		if (input[i] == '$')
			tmp = handle_dollar(input, &i, env, status);
		else
			tmp = extract_plain(input, &i);
		if (!tmp)
		{
			free(result);
			return (ft_strdup(""));
		}
		result = ft_strjoin_free(result, tmp);
	}
	return (result);
}

void	expand_token(t_token *tok, t_env *env, int status)
{
	char	*expanded;
	char	*normalized;

	if (ft_strcmp(tok->value, "$") == 0)
		return ;
	expanded = ft_expand_value(tok->value, env, status);
	if (!expanded)
	{
		free(tok->value);
		tok->value = ft_strdup("");
		return ;
	}
	if (tok->quote_type == '\0' || tok->quote_type == '"')
	{
		normalized = normalize_whitespace(expanded);
		free(expanded);
		handle_normalized_expansion(tok, normalized);
		return ;
	}
	tok->value = expanded;
}

void	ft_expand_tokens(t_token *tokens, t_env *env, int status)
{
	t_token	*prev;
	t_token	*next;

	prev = NULL;
	while (tokens)
	{
		next = tokens->next;
		handle_export_assignment(prev, &tokens, env, status);
		if (!tokens)
			break ;
		handle_tilde_and_skip(&tokens, prev, next);
		if (!tokens)
			break ;
		handle_regular_expansion(tokens, env, status);
		prev = tokens;
		tokens = tokens->next;
	}
}

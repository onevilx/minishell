/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse7.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouftou <obouftou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:06:07 by obouftou          #+#    #+#             */
/*   Updated: 2025/06/24 16:39:19 by obouftou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

void	handle_normalized_expansion(t_token *tok, char *expanded)
{
	t_token	*new_tokens;

	if (ft_strchr(expanded, ' '))
	{
		new_tokens = split_expanded_token(expanded);
		replace_token_with_multiple(tok, new_tokens);
		free(expanded);
	}
	else
		tok->value = expanded;
}

static void	init_norm_vars(int *i, int *j, int *in_space)
{
	*i = 0;
	*j = 0;
	*in_space = 0;
}

static void	handle_char(char *res, char c, int *j, int *in_space)
{
	res[(*j)++] = c;
	*in_space = 0;
}

static void	handle_space(char *res, int *j, int *in_space)
{
	if (!*in_space && *j > 0)
		res[(*j)++] = ' ';
	*in_space = 1;
}

char	*normalize_whitespace(char *str)
{
	char	*res;
	int		i;
	int		j;
	int		in_space;

	if (!str)
		return (NULL);
	res = g_malloc(ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	init_norm_vars(&i, &j, &in_space);
	while (str[i])
	{
		if (ft_isspace((unsigned char)str[i]))
			handle_space(res, &j, &in_space);
		else
			handle_char(res, str[i], &j, &in_space);
		i++;
	}
	res[j] = '\0';
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars9.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouftou <obouftou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:38:46 by obouftou          #+#    #+#             */
/*   Updated: 2025/06/24 20:42:48 by obouftou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

int	is_operator_start(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_meta(char c)
{
	return (c == ' ' || c == '\t'
		|| c == '|' || c == '<' || c == '>'
		|| c == '\'' || c == '"');
}

t_token	*parse_quoted_word(const char *input, int *i)
{
	char	quote;
	char	buffer[1024];
	int		buf_i;

	buf_i = 0;
	quote = input[(*i)++];
	while (input[*i] && input[*i] != quote && buf_i < 1023)
		buffer[buf_i++] = input[(*i)++];
	if (input[*i] == quote)
		(*i)++;
	buffer[buf_i] = '\0';
	return (new_token(WORD, ft_strdup(buffer), quote));
}

void	skip_spaces(const char *input, int *i)
{
	while (input[*i] && ft_isspace(input[*i]))
		(*i)++;
}

bool	has_space_after(const char *input, int i)
{
	while (input[i])
	{
		if (ft_isspace(input[i]))
			return (true);
		if (!ft_isspace(input[i]))
			break ;
		i++;
	}
	return (false);
}

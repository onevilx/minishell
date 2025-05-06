/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouftou <obouftou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:03:35 by obouftou          #+#    #+#             */
/*   Updated: 2025/05/05 21:03:33 by obouftou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

bool	are_quotes_closed(const char *input)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (input[i])
	{
		if ((input[i] == '\'' || input[i] == '"') && quote == 0)
			quote = input[i];
		else if (input[i] == quote)
			quote = 0;
		i++;
	}
	return (quote == 0);
}

char	*collect_quoted_content(const char *input, int *i, char *quote_type)
{
	char	quote;
	char	buffer[1024];
	int		buf_i;

	buf_i = 0;
	quote = input[(*i)++];
	if (quote_type)
		*quote_type = quote;
	while (input[*i] && input[*i] != quote)
	{
		buffer[buf_i++] = input[(*i)++];
		if (buf_i >= 1023)
			break ;
	}
	if (input[*i] == quote)
		(*i)++;
	buffer[buf_i] = '\0';
	return (strdup(buffer));
}

int	copy_to_buffer(char *dst, int buf_i, const char *src)
{
	int	j;

	j = 0;
	while (src[j])
	{
		if (buf_i >= 1023)
			break ;
		dst[buf_i++] = src[j++];
	}
	return (buf_i);
}

void	init(char *quote_type, int *buff_i)
{
	*buff_i = 0;
	*quote_type = '\0';
}

t_token	*parse_word(const char *input, int *i)
{
	char	buffer[1024];
	int		buf_i;
	char	*quoted;
	char	quote_type;

	init(&quote_type, &buf_i);
	while (input[*i] && !ft_isspace(input[*i]) && !is_operator_start(input[*i]))
	{
		if (input[*i] == '\'' || input[*i] == '"')
		{
			quoted = collect_quoted_content(input, i, &quote_type);
			if (!quoted)
				return (NULL);
			buf_i = copy_to_buffer(buffer, buf_i, quoted);
			free(quoted);
		}
		else
		{
			buffer[buf_i++] = input[(*i)++];
			if (buf_i >= 1023)
				break ;
		}
	}
	buffer[buf_i] = '\0';
	return (new_token(WORD, strdup(buffer), quote_type));
}

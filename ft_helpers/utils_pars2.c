/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouftou <obouftou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:03:35 by obouftou          #+#    #+#             */
/*   Updated: 2025/06/06 00:12:05 by obouftou         ###   ########.fr       */
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
	char	buffer[1000000];
	int		buf_i;

	buf_i = 0;
	quote = input[(*i)++];
	if (quote_type)
		*quote_type = quote;
	while (input[*i] && input[*i] != quote)
	{
		buffer[buf_i++] = input[(*i)++];
		if (buf_i >= 1000000)
			break ;
	}
	if (input[*i] == quote)
		(*i)++;
	buffer[buf_i] = '\0';
	return (ft_strdup(buffer));
}

int	copy_to_buffer(char *dst, int buf_i, const char *src)
{
	int	j;

	j = 0;
	while (src[j])
	{
		if (buf_i >= 1000000)
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

static void	init_parse(char *qt, int *buf_i)
{
	*qt = '\0';
	*buf_i = 0;
}

static int	copy_token_part(char *dst, int buf_i, const char *src)
{
	int	j;

	j = 0;
	while (src[j] && buf_i < 1000000)
		dst[buf_i++] = src[j++];
	return (buf_i);
}

static int	handle_quoted_part(const char *input, int *i, char *buf, int buf_i, char *qt)
{
	char	*quoted;

	quoted = collect_quoted_content(input, i, qt);
	if (!quoted)
		return (-1);
	buf_i = copy_token_part(buf, buf_i, quoted);
	free(quoted);
	return (buf_i);
}

t_token	*parse_word(const char *input, int *i)
{
	char	buffer[1000000];
	char	qt;
	int		buf_i;

	init_parse(&qt, &buf_i);
	while (input[*i] && !ft_isspace(input[*i]) && !is_operator_start(input[*i]))
	{
		if (input[*i] == '\'' || input[*i] == '"')
		{
			buf_i = handle_quoted_part(input, i, buffer, buf_i, &qt);
			if (buf_i == -1)
				return (NULL);
		}
		else
		{
			buffer[buf_i++] = input[(*i)++];
			if (buf_i >= 100000)
				break ;
		}
	}
	buffer[buf_i] = '\0';
	return (new_token(WORD, ft_strdup(buffer), qt));
}

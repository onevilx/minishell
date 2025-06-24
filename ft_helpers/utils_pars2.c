/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouftou <obouftou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:03:35 by obouftou          #+#    #+#             */
/*   Updated: 2025/06/24 17:27:39 by obouftou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

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

int	copy_token_part(char *dst, int buf_i, const char *src)
{
	int	j;

	j = 0;
	while (src[j] && buf_i < 1000000)
		dst[buf_i++] = src[j++];
	return (buf_i);
}

t_token	*parse_word(const char *input, int *i)
{
	t_parse_ctx	ctx;
	int			res;

	init_parse(&ctx.qt, &ctx.buf_i);
	while (input[*i] && !ft_isspace(input[*i])
		&& !is_operator_start(input[*i]))
	{
		if (input[*i] == '\'' || input[*i] == '"')
		{
			res = handle_quoted_part(input, i, &ctx);
			if (res == -1)
				return (NULL);
		}
		else if (ctx.buf_i < 100000)
			ctx.buf[ctx.buf_i++] = input[(*i)++];
	}
	ctx.buf[ctx.buf_i] = '\0';
	return (new_token(WORD, ft_strdup(ctx.buf), ctx.qt));
}

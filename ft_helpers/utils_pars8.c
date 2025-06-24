/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars8.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:40:30 by obouftou          #+#    #+#             */
/*   Updated: 2025/06/24 19:04:45 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

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

int	handle_quoted_part(const char *input, int *i, t_parse_ctx *ctx)
{
	char	*quoted;

	quoted = collect_quoted_content(input, i, &ctx->qt);
	if (!quoted)
		return (-1);
	ctx->buf_i = copy_token_part(ctx->buf, ctx->buf_i, quoted);
	free(quoted);
	return (ctx->buf_i);
}

char	*process_line(const char *line, t_env *env,
			char quote_type, int exit_status)
{
	t_token	*token;
	char	*j_line;

	if (!quote_type)
	{
		token = tokenizing((char *)line);
		ft_expand_tokens(token, env, exit_status);
		merge_tokens(token);
		j_line = join_token_values(token);
	}
	else
		j_line = ft_strdup(line);
	return (j_line);
}

char	*append_line(char *buffer, char *line)
{
	char	*tmp;

	tmp = ft_strjoin(buffer, line);
	free(buffer);
	buffer = tmp;
	tmp = ft_strjoin(buffer, "\n");
	free(buffer);
	return (tmp);
}

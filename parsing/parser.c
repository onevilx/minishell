/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouftou <obouftou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:34:57 by obouftou          #+#    #+#             */
/*   Updated: 2025/04/22 20:57:12 by obouftou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

int is_meta(char c)
{
	return (c == ' ' || c == '\t' || c == '|' || c == '<' || c == '>' || c == '\'' || c == '"');
}

t_token *parse_word(const char *input, int *i)
{
	int start = *i;
	while (input[*i] && !is_meta(input[*i]))
		(*i)++;
	int len = *i - start;
	char *val = strndup(&input[start], len);
	return new_token(WORD, val);
}


t_token *parse_quoted_word(const char *input, int *i)
{
	char quote = input[*i];
	int start = ++(*i);
	while (input[*i] && input[*i] != quote)
		(*i)++;
	int len = *i - start;
	char *val = strndup(&input[start], len);
	if (input[*i] == quote)
		(*i)++;
	return new_token(WORD, val);
}

int	is_operator_start(char c)
{
	return (c == '|' || c == '<' || c == '>');
}
t_token *tokenizing(const char *input)
{
	int i = 0;
	t_token *tokens = NULL;

	while (input[i])
	{
		if (is_whitespace(input[i]))
		{
			i++;
			continue;
		}
		if (is_operator_start(input[i]))
		{
			add_token(&tokens, parse_operator(input, &i));
			continue;
		}
		if (input[i] == '\'' || input[i] == '"')
		{
			add_token(&tokens, parse_quoted_word(input, &i));
			continue;
		}
		add_token(&tokens, parse_word(input, &i));
	}
	return tokens;
}

t_cmd	*ft_input_proces(char *input)
{
	t_token	*tokens;
	t_cmd	*cmd;

	tokens = toknizing(input);
	if(tokens)
	{
		santax_check();

	}




	return (cmd);
}

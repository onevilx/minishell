/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:34:57 by obouftou          #+#    #+#             */
/*   Updated: 2025/04/23 15:04:16 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniheader.h"


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

	tokens = tokenizing(input);
	if(tokens)
	{
		santax_check();

	}




	return (cmd);
}

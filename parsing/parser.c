/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:34:57 by obouftou          #+#    #+#             */
/*   Updated: 2025/04/25 01:43:09 by yaboukir         ###   ########.fr       */
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
		if (ft_isspace(input[i]))
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

void ft_print_tokens(t_token *tokens)
{
	t_token *cur = tokens;

	printf("🔎 Token list:\n");
	while (cur)
	{
		printf("  Type: %-10s | Value: \"%s\"\n",
			cur->type == WORD ? "WORD" :
			cur->type == PIPE ? "PIPE" :
			cur->type == REDIR_IN ? "REDIR_IN" :
			cur->type == REDIR_OUT ? "REDIR_OUT" :
			cur->type == APPEND ? "APPEND" :
			cur->type == HEREDOC ? "HEREDOC" : "UNKNOWN",
			cur->value);
		cur = cur->next;
	}
}

t_cmd	*ft_input_proces(char *input)
{
	t_token	*tokens;

	tokens = tokenizing(input);
	if (!tokens)
		return(NULL);
	ft_print_tokens(tokens);
	// if(tokens)
	// {
	// 	santax_check(tokens);
	// }
	// return (cmd);
	return (NULL);
}

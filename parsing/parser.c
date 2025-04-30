/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouftou <obouftou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:34:57 by obouftou          #+#    #+#             */
/*   Updated: 2025/04/30 18:32:01 by obouftou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

int	is_meta(char c)
{
	return (c == ' ' || c == '\t'
		|| c == '|' || c == '<' || c == '>'
		|| c == '\'' || c == '"');
}

t_token	*parse_word(const char *input, int *i)
{
	int		start;
	int		len;
	char	*val;

	start = *i;
	while (input[*i] && !is_meta(input[*i]))
		(*i)++;
	len = *i - start;
	val = strndup(&input[start], len);
	return (new_token(WORD, val));
}


t_token	*parse_quoted_word(const char *input, int *i)
{
	char	quote;
	int		start;

	start = ++(*i);
	quote = input[*i];
	while (input[*i] && input[*i] != quote)
		(*i)++;
	int len = *i - start;
	char *val = strndup(&input[start], len);
	if (input[*i] == quote)
		(*i)++;
	return (new_token(WORD, val));
}

int	is_operator_start(char c)
{
	return (c == '|' || c == '<' || c == '>');
}
t_token	*tokenizing(const char *input)
{
	int		i;
	t_token	*tokens;

	tokens = NULL;
	i = 0;
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
	return (tokens);
}

void	ft_print_tokens(t_token *tokens)
{
	t_token	*cur;

	cur = tokens;
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
	// t_cmd	*cmd;

	if (!are_quotes_closed(input))
	{
		printf("Syntax error: unclosed quote\n");
		return (NULL);
	}
	tokens = tokenizing(input);
	if (!tokens)
		return(NULL);
	ft_print_tokens(tokens);
	if(!syntax_check(tokens))
	{
		free_tokens(tokens);
		return (NULL);
	}
	//return (cmd);
	return(NULL);
}

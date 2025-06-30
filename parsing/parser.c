/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:34:57 by obouftou          #+#    #+#             */
/*   Updated: 2025/06/30 18:01:57 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

static t_token	*parse_dollar_quote_case(const char *input, int *i)
{
	(*i)++;
	return (parse_quoted_word(input, i));
}

static t_token	*parse_non_empty_word(const char *input, int *i)
{
	t_token	*new;

	new = parse_word(input, i);
	if (new && new->value && new->value[0] == '\0')
	{
		free(new->value);
		free(new);
		return (NULL);
	}
	return (new);
}

static t_token	*parse_and_classify(const char *input, int *i)
{
	t_token	*new;

	new = NULL;
	if (is_operator_start(input[*i]))
		new = parse_operator(input, i);
	else if (input[*i] == '$' && input[*i + 1] == '"')
		new = parse_dollar_quote_case(input, i);
	else if (input[*i] == '"' || input[*i] == '\'')
	{
		new = parse_quoted_word(input, i);
		if (new->value[0] == '\0')
			new->not_hide = true;
	}
	else
		new = parse_non_empty_word(input, i);
	return (new);
}

t_token	*tokenizing(const char *input)
{
	t_token	*tokens;
	t_token	*new;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		skip_spaces(input, &i);
		new = parse_and_classify(input, &i);
		if (new)
		{
			if (new->value && new->value[0] == '\0')
				new->not_hide = true;
			new->space_after = has_space_after(input, i);
			add_token(&tokens, new);
		}
	}
	return (tokens);
}

t_cmd	*ft_input_proces(char *input, char **envp, int *exit_status)
{
	t_token	*tokens;
	t_cmd	*cmd;
	t_env	*env;

	if (!are_quotes_closed(input))
	{
		printf("Syntax error: unclosed quote\n");
		*exit_status = 258;
		return (NULL);
	}
	tokens = tokenizing(input);
	if (!tokens)
		return (NULL);
	if (!syntax_check(tokens, exit_status))
		return (NULL);
	normalize_odd_dollars(tokens);
	env = ft_init_env_list(envp);
	ft_expand_tokens(tokens, env, *exit_status);
	merge_tokens(tokens);
	if (!check_ambg(tokens, exit_status))
		return (NULL);
	ft_remove_empty(&tokens);
	cmd = ft_parse_commands(tokens);
	return (cmd);
}

#include "../includes/protos.h"

static char	*get_env_val_list(t_env *env, const char *key)
{
	while(env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return ("");
}

static char	*extract_plain(char *input, int *i)
{
	int	start;

	start = *i;
	while (input[*i] && input[*i] != '$')
		(*i)++;
	return (ft_substr(input, start, *i - start));
}


static char	*handle_dollar(char *input, int *i, t_env *env, int status)
{
	int		start;
	char	*name;

	(*i)++;
	if (input[*i] == '?')
		return (ft_itoa(((*i)++, status)));
	if (!ft_isalpha(input[*i]) && input[*i] != '_')
		return (ft_strdup(""));

	start = *i;
	while (ft_isalnum(input[*i]) || input[*i] == '_')
		(*i)++;
	name = ft_substr(input, start, *i - start);
	return (ft_strdup(get_env_val_list(env, name)));
}

char	*ft_expand_value(char *input, t_env *env, int status)
{
	char	*result;
	char	*tmp;
	int		i;

	i = 0;
	result = ft_strdup("");
	while (input[i])
	{
		if (input[i] == '$')
			tmp = handle_dollar(input, &i, env, status);
		else
			tmp = extract_plain(input, &i);
		if (!tmp)
		{
			// free(result);
			return (ft_strdup(""));
		}
		result = ft_strjoin_free(result, tmp);
	}
	return (result);
}

static bool	is_localized_string(t_token *prev)
{
	return (prev && prev->quote_type == '"'
		&& ft_strcmp(prev->value, "$") == 0);
}

void	replace_token_with_multiple(t_token *old, t_token *new_tokens)
{
	t_token	*next = old->next;
	t_token	*first = new_tokens;
	t_token	*last;

	if (!first)
		return ;

	last = first;
	while (last->next)
		last = last->next;

	// Preserve the rest of the list
	last->next = next;
	// Overwrite the current token with the first new token
	old->type = first->type;
	old->value = first->value;
	old->quote_type = first->quote_type;
	old->space_after = first->space_after;
	old->next = first->next;
	// free(first);
}



t_token	*split_expanded_token(char *expanded)
{
	char	**parts = ft_split(expanded, ' ');
	t_token	*head = NULL;
	t_token	*new;
	int		i = 0;

	while (parts[i])
	{
		new = new_token(WORD, ft_strdup(parts[i]), '\0');
		add_token(&head, new);
		i++;
	}
	// free_split(parts);
	return (head);
}



static void	expand_token(t_token *tok, t_env *env, int status)
{
	char		*expanded;
	t_token		*new_tokens;

	if (ft_strcmp(tok->value, "$") == 0)
		return ;

	expanded = ft_expand_value(tok->value, env, status);
	if (!expanded)
	{
		free(tok->value);
		tok->value = ft_strdup("");
		return ;
	}
	if (tok->quote_type == '\0' && ft_strchr(expanded, ' '))
	{
		new_tokens = split_expanded_token(expanded);
		replace_token_with_multiple(tok, new_tokens);
		// free(expanded);
		return ;
	}
	// free(tok->value);
	tok->value = expanded;
}



void	ft_expand_tokens(t_token *tokens, t_env *env, int status)
{
	t_token	*prev = NULL;
	t_token	*next;

	while (tokens)
	{
		next = tokens->next;
		if (is_localized_string(prev) || tokens->quote_type == '\'')
		{
			prev = tokens;
			tokens = next;
			continue ;
		}
		if (ft_strcmp(tokens->value, "~") == 0)
		{
			free(tokens->value);
			tokens->value = ft_strdup("$HOME");
		}
		if (ft_strchr(tokens->value, '$') &&
			(tokens->quote_type == '\0' || tokens->quote_type == '"'))
		{
			expand_token(tokens, env, status);
		}
		prev = tokens;
		tokens = tokens->next;
	}
}

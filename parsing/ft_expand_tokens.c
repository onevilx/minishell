


//so know i got an idea of storing the 2d array into an linked list so i can easly backtrace what i need and traverse it freely ]
// so i will get the envp into linked list by soting every env[1] into t_env value/ key
// so ill creat a function that split every string of the env pointer to two part befor '=' and assinge it to the key and the after '=' and assigne it to the value;
// costume split in the way same concept but the delimiter will be the = ;
//and so on till i get all the envirement stored in my linnked list;;

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

static char	*ft_expand_value(char *input, t_env *env, int status)
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
			free(result);
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


static void	expand_token(t_token *tok, t_env *env, int status)
{
	char	*expanded;

	if (ft_strcmp(tok->value, "$") == 0)
		return ;
	expanded = ft_expand_value(tok->value, env, status);
	if (!expanded)
	{
		free(tok->value);
		tok->value = ft_strdup("");
		return ;
	}
	free(tok->value);
	tok->value = expanded;
}



void	ft_expand_tokens(t_token *tokens, t_env *env, int status)
{
	t_token	*prev;

	prev = NULL;
	while (tokens)
	{
		if (is_localized_string(prev) || tokens->quote_type == '\'')
		{
			prev = tokens;
			if (tokens->next)
				tokens = tokens->next;
		}
		if (ft_strchr(tokens->value, '$')
			&& (tokens->quote_type == '\0' || tokens->quote_type == '"'))
			expand_token(tokens, env, status);
		prev = tokens;
		tokens = tokens->next;
	}
}




// void	ft_expand_tokens(t_token *tokens, t_env *env, int exit_status)
// {
// 	t_token	*prev;
// 	char	*expanded;

// 	prev = NULL;
// 	while (tokens)
// 	{
// 		if ((prev && prev->quote_type == '"' && ft_strcmp(prev->value, "$") == 0)
// 			|| tokens->quote_type == '\'')
// 		{
// 			prev = tokens;
// 			tokens = tokens->next;
// 			continue ;
// 		}

// 		if (ft_strchr(tokens->value, '$')
// 			&& (tokens->quote_type == '\0' || tokens->quote_type == '"'))
// 		{
// 			expanded = ft_expand_value(tokens->value, env, exit_status);
// 			if (!expanded)
// 			{
// 				prev = tokens;
// 				tokens = tokens->next;
// 				continue ;
// 			}
// 			free(tokens->value);
// 			tokens->value = expanded;
// 		}
// 		prev = tokens;
// 		tokens = tokens->next;
// 	}
// }





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

static char	*ft_expand_value(char *input, t_env *env, int exit_status)
{
	int		i;
	char	*result;
	char	*tmp;

	i = 0;
	result = ft_strdup("");
	while (input[i])
	{
		if (input[i] == '$')
			tmp = handle_dollar(input, &i, env, exit_status);
		else
			tmp = extract_plain(input, &i);
		if (!tmp)
			return (free(result), NULL);
		result = ft_strjoin_free(result, tmp);
	}
	return (result);
}


void	ft_expand_tokens(t_token *tokens, t_env *env, int exit_status)
{
	char	*expanded;

	while (tokens)
	{
		if (tokens->quote_type == '\'')
		{
			if (tokens->next)
				tokens = tokens->next;
		}
		else if (ft_strchr(tokens->value, '$')
			&& (tokens->quote_type == '\0' || tokens->quote_type == '"'))
			{
				expanded = ft_expand_value(tokens->value, env, exit_status);
				if (!expanded)
				{
					tokens = tokens->next;
					continue ;
				}
				free(tokens->value);
				tokens->value = expanded;
			}
		tokens = tokens->next;
	}
}

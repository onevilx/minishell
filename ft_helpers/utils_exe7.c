/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe7.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 00:58:58 by yaboukir          #+#    #+#             */
/*   Updated: 2025/06/19 20:40:22 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

void	free_redirections(t_redirect *redir)
{
	t_redirect	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->val);
		free(redir);
		redir = tmp;
	}
}

void	free_tokensexe(t_token **tokens)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

int	is_append_mode(char *arg, int *pos)
{
	int	i = 0;

	while (arg[i] && arg[i] != '=')
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
		{
			*pos = i;
			return (1);
		}
		i++;
	}
	*pos = i;
	return (0);
}

void	append_to_env(char *key, char *value, int idx)
{
	char	*existing;
	char	*joined;
	char	*new_value;

	if (idx >= 0)
	{
		existing = ft_strdup(ft_strchr((*get_env())[idx], '=') + 1);
		joined = ft_strjoin(existing, value);
		new_value = ft_strjoin3(key, "=", joined);
		update_env_var(idx, new_value);
		free(existing);
		free(joined);
		free(new_value);
	}
	else
		add_env_var(ft_strjoin3(key, "=", value));
}

void	add_env_var(char *arg)
{
	char	**env;
	char	**new_env;
	int		i;

	env = *get_env();
	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return ;
	i = -1;
	while (env[++i])
		new_env[i] = env[i];
	new_env[i++] = ft_strdup(arg);
	new_env[i] = NULL;
	free(env);
	*get_env() = new_env;
}

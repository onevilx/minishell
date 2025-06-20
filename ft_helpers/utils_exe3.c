/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouftou <obouftou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:45:52 by yaboukir          #+#    #+#             */
/*   Updated: 2025/06/20 17:58:17 by obouftou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

char	**copy_env(char **envp)
{
	char	**env_copy;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	env_copy = g_malloc(sizeof(char *) * (i + 1));
	if (!env_copy)
		return (NULL);
	i = -1;
	while (envp[++i])
		env_copy[i] = ft_strdup(envp[i]);
	env_copy[i] = NULL;
	return (env_copy);
}

void	update_shlvl(void)
{
	char	*lvl;
	int		shlvl;
	char	*lvl_str;
	char	*shlvl_str;

	lvl = getenv("SHLVL");
	if (!lvl)
		shlvl = 1;
	else
		shlvl = ft_atoi(lvl) + 1;
	if (shlvl < 0)
		shlvl = 0;
	lvl_str = ft_itoa(shlvl);
	shlvl_str = ft_strjoin("SHLVL=", lvl_str);
	update_or_add_env("SHLVL", shlvl_str);
	free(lvl_str);
	free(shlvl_str);
}

static char	**copy_env_and_add(char **env, const char *full_var, int count)
{
	char	**new_env;
	int		i;

	new_env = g_malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			while (i--)
				free(new_env[i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i++] = ft_strdup(full_var);
	new_env[i] = NULL;
	return (new_env);
}

void	update_or_add_env(const char *key, const char *full_var)
{
	char	**env;
	char	**new_env;
	size_t	len;
	int		i;

	env = *get_env();
	len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, len) && env[i][len] == '=')
		{
			free(env[i]);
			env[i] = ft_strdup(full_var);
			return ;
		}
		i++;
	}
	new_env = copy_env_and_add(env, full_var, i);
	if (!new_env)
		return ;
	free_env(env);
	*get_env() = new_env;
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->token)
			free_tokensexe(cmd->token);
		if (cmd->args)
		{
			free_args_list(cmd->args);
			free(cmd->args);
		}
		free_redirections(cmd->red);
		free(cmd);
		cmd = tmp;
	}
}

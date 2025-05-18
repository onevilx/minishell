/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onevil_x <onevil_x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:47:14 by yaboukir          #+#    #+#             */
/*   Updated: 2025/05/18 05:09:40 by onevil_x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

char	***get_env(void)
{
	static char	**env = NULL;

	return (&env);
}

char	*get_env_value(char *key)
{
	char	**env;
	int		i;
	int		len;

	env = *get_env();
	len = ft_strlen(key);
	i = 0;
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], key, len) && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

void	update_env_var(int idx, char *arg)
{
	char	**env;

	env = *get_env();
	free(env[idx]);
	env[idx] = ft_strdup(arg);
}

int	find_env_index(char **env, char *key)
{
	int		i;
	size_t	len;

	len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, len) && env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	init_env(char **envp)
{
	char	**env_copy;

	env_copy = copy_env(envp);
	if (!env_copy)
		return ;
	*get_env() = env_copy;
	update_shlvl();
}

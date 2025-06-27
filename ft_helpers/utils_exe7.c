/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe7.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouftou <obouftou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 00:58:58 by yaboukir          #+#    #+#             */
/*   Updated: 2025/06/27 00:24:11 by obouftou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

int	is_append_mode(char *arg, int *pos)
{
	int	i;

	i = 0;
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
	new_env = g_malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return ;
	i = -1;
	while (env[++i])
		new_env[i] = env[i];
	new_env[i++] = ft_strdup(arg);
	new_env[i] = NULL;
	*get_env() = new_env;
}

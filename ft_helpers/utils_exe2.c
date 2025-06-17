/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouftou <obouftou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:32:02 by yaboukir          #+#    #+#             */
/*   Updated: 2025/06/17 22:40:49 by obouftou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

char	*read_input(const char *delimiter, t_env *env, int exit_status)
{
	char	*line;
	char	*buffer;
	char	*tmp;
	char	*expanded;

	buffer = ft_strdup("");
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
			break ;
		if (ft_strchr(delimiter, '\'') && ft_strchr(delimiter, '"'))
			expanded = ft_strdup(line);
		else
			expanded = ft_expand_value(line, env, exit_status);
		tmp = ft_strjoin(buffer, expanded);
		free(buffer);
		buffer = tmp;
		buffer = ft_strjoin(buffer, "\n");
		free(line);
	}
	free(line);
	return (buffer);
}

void	free_split(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*joined;

	if (!s1 || !s2)
		return (NULL);
	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}

void	update_pwd_vars(char *oldpwd)
{
	char	cwd[PATH_MAX];
	char	*oldpwd_var;
	char	*pwd_var;

	oldpwd_var = ft_strjoin("OLDPWD=", oldpwd);
	update_or_add_env("OLDPWD", oldpwd_var);
	free(oldpwd_var);

	if (getcwd(cwd, sizeof(cwd)))
	{
		pwd_var = ft_strjoin("PWD=", cwd);
		update_or_add_env("PWD", pwd_var);
		free(pwd_var);
	}
}

void	free_env(char **env)
{
	int i = 0;
	if (!env)
		return ;
	while (env[i])
		free(env[i++]);
	free(env);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onevil_x <onevil_x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:32:02 by yaboukir          #+#    #+#             */
/*   Updated: 2025/06/05 16:45:48 by onevil_x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

char	*read_input(const char *delimiter)
{
	char	*line;
	char	*buffer;
	char	*tmp;

	buffer = ft_strdup("");
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
			break ;
		tmp = ft_strjoin(buffer, line);
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

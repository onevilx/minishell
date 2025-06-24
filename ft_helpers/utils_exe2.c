/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:32:02 by yaboukir          #+#    #+#             */
/*   Updated: 2025/06/24 19:07:42 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

char	*join_token_values(t_token *tokens)
{
	char	*result;
	char	*tmp;

	result = ft_strdup("");
	while (tokens)
	{
		tmp = result;
		result = ft_strjoin(result, tokens->value);
		free(tmp);
		if (tokens->space_after)
		{
			tmp = result;
			result = ft_strjoin(result, " ");
			free(tmp);
		}
		tokens = tokens->next;
	}
	return (result);
}

char	*read_input(const char *delimiter, t_env *env,
			char quote_type, int exit_status)
{
	return (handle_read_loop((char *)delimiter, env,
			quote_type, exit_status));
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

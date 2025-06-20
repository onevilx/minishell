/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouftou <obouftou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:32:02 by yaboukir          #+#    #+#             */
/*   Updated: 2025/06/20 18:12:57 by obouftou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

char	*join_token_values(t_token *tokens)
{
	char	*result = ft_strdup("");
	char	*tmp;

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


char	*read_input(const char *delimiter, t_env *env, char quote_type, int exit_status)
{
	char	*line;
	char	*buffer;
	char	*tmp;
	t_token *token;
	char	*j_line;

	buffer = ft_strdup("");
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
			break ;
		if (!quote_type)
		{
			token = tokenizing(line);
			ft_expand_tokens(token, env, exit_status);
			merge_tokens(token);
			j_line = join_token_values(token);
			// free_tokens(token);
		}
		else
			j_line = ft_strdup(line);
		tmp = ft_strjoin(buffer, j_line);
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

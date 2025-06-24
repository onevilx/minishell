/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:09:21 by yaboukir          #+#    #+#             */
/*   Updated: 2025/06/24 18:23:01 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

void	ft_free_split(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

char	*find_command_path(char *cmd, char **env)
{
	char	**paths;
	int		i;

	if (!cmd || !env)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		return (NULL);
	paths = ft_split(env[i] + 5, ':');
	if (!paths)
		return (NULL);
	return (find_in_paths(paths, cmd));
}

char	**convert_args(t_arg *args)
{
	int		i;
	int		count;
	char	**argv;
	t_arg	*tmp;

	count = 0;
	tmp = args;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	argv = g_malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	tmp = args;
	i = 0;
	while (i < count)
	{
		argv[i] = tmp->value;
		tmp = tmp->next;
		i++;
	}
	argv[count] = NULL;
	return (argv);
}

void	handle_pipe(t_cmd *cmd)
{
	pipe_loop(cmd);
}

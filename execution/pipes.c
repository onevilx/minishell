/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:09:21 by yaboukir          #+#    #+#             */
/*   Updated: 2025/05/16 00:18:13 by yaboukir         ###   ########.fr       */
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
	char	*path;
	char	**paths;
	char	*tmp;
	int		i;

	i = 0;
	path = NULL;
	if (!cmd || !env || access(cmd, X_OK) == 0)
		return (strdup(cmd));
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		return (NULL);
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths && paths[i++])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, X_OK) == 0)
			return (ft_free_split(paths), path);
		free(path);
	}
	return (ft_free_split(paths), NULL);
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
	argv = malloc(sizeof(char *) * (count + 1));
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
	int		pipe_fd[2];
	int		prev_fd;
	pid_t	pid;
	t_cmd	*current;

	prev_fd = -1;
	current = cmd;
	while (current)
	{
		if (current->next && pipe(pipe_fd) == -1)
			return (perror("pipe"), (void)0);
		pid = fork();
		if (pid == -1)
			return (perror("fork"), (void)0);
		else if (pid == 0)
			handle_child_process(current, prev_fd, pipe_fd);
		else
			handle_parent_process(current, &prev_fd, pipe_fd);
		current = current->next;
	}
	while (wait(NULL) > 0)
		;
}

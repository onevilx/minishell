/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe12.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 02:59:00 by yaboukir          #+#    #+#             */
/*   Updated: 2025/06/30 23:00:11 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

int	create_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}

pid_t	do_fork(pid_t last_pid, int pipe_fd[2], int prev_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		wait_for_children(last_pid);
		perror("fork");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		if (prev_fd != -1)
			close(prev_fd);
		return (-1);
	}
	return (pid);
}

char	**get_paths_array(void)
{
	char		*path_env;
	char		**paths;
	static char	*fallback_paths[] = {"/bin", "/usr/bin", NULL};

	path_env = get_env_value("PATH");
	if (!path_env || path_env[0] == '\0')
		return (fallback_paths);
	paths = ft_split(path_env, ':');
	if (!paths)
	{
		perror("PATH");
		exit(127);
	}
	return (paths);
}

void	try_exec_in_paths(char **paths, char **args_array, char **env)
{
	int		i;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin_free(full_path, args_array[0]);
		if (access(full_path, X_OK) == 0)
			execve(full_path, args_array, env);
		free(full_path);
		i++;
	}
}

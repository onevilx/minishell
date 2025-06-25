/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe11.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 20:33:33 by yaboukir          #+#    #+#             */
/*   Updated: 2025/06/25 00:26:41 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

int	is_directory(const char *path)
{
	int	fd;

	fd = open(path, O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		return (1);
	}
	return (0);
}

char	*find_in_paths(char **paths, char *cmd)
{
	char	*tmp;
	char	*path;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, X_OK) == 0)
		{
			ft_free_split(paths);
			return (path);
		}
		free(path);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}

static void	wait_for_children(pid_t last_pid)
{
	int	status;

	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status) && last_pid != 0)
			*get_exit_status() = WEXITSTATUS(status);
	}
}

void	pipe_loop(t_cmd *cmd)
{
	t_cmd	*current;
	pid_t	pid;
	pid_t	last_pid;
	int		pipe_fd[2];
	int		prev_fd;

	current = cmd;
	prev_fd = -1;
	last_pid = 0;
	while (current)
	{
		if (current->next && pipe(pipe_fd) == -1)
			return (perror("pipe"), (void)0);
		pid = fork();
		if (pid == -1)
			return (perror("fork"), (void)0);
		else if (pid == 0)
			handle_child_process(current, prev_fd, pipe_fd);
		if (!current->next)
			last_pid = pid;
		handle_parent_process(current, &prev_fd, pipe_fd);
		current = current->next;
	}
	wait_for_children(last_pid);
}

char	*handle_read_loop(char *delimiter, t_env *env,
			char quote_type, int exit_status)
{
	char	*line;
	char	*buffer;
	char	*j_line;

	buffer = ft_strdup("");
	if (!buffer)
		return (NULL);
	signal(SIGINT, heredoc_sig);
	while (1)
	{
		line = readline("> ");
		if (!line && g_signal == 1)
			return (handle_ctrl_c(buffer));
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		j_line = process_line(line, env, quote_type, exit_status);
		free(line);
		buffer = append_line(buffer, j_line);
		free(j_line);
	}
	signal(SIGINT, sigint_handler);
	return (buffer);
}

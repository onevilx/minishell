/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:09:21 by yaboukir          #+#    #+#             */
/*   Updated: 2025/05/14 12:04:27 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

void handle_pipe(t_cmd *cmd)
{
	int i;
	int pipe_fd[2];
	int prev_fd;
	pid_t pid;

	i = 0;
	prev_fd = -1;
	while (i < cmd->pipe_count)
	{
		if (i < cmd->pipe_count - 1 && pipe(pipe_fd) == -1)
			perror("pipe");
		pid = fork();
		if (pid == -1)
			perror("fork");
		else if (pid == 0)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (i < cmd->pipe_count - 1)
			{
				close(pipe_fd[0]);
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[1]);
			}
			execve(cmd->args[i][0], cmd->args[i], *get_env());
			exit(1);
		}
		else
		{
			if (prev_fd != -1)
				close(prev_fd);
			if (i < cmd->pipe_count - 1)
			{
				close(pipe_fd[1]);
				prev_fd = pipe_fd[0];
			}
		}
		i++;
	}
	while (wait(NULL) > 0)
		;
}

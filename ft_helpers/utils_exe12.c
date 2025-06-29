/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe12.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 02:59:00 by yaboukir          #+#    #+#             */
/*   Updated: 2025/06/29 03:00:18 by yaboukir         ###   ########.fr       */
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

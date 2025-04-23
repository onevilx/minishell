/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:09:21 by yaboukir          #+#    #+#             */
/*   Updated: 2025/04/22 23:13:19 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "execution.h"

void	handle_pipe(t_cmd *cmd)
{
	int pipe_fd[2];
	pid_t pid;
	int i;

	i = 0;
	while (i < cmd->pipe_count)
	{
		pipe(pipe_fd);
		pid = fork();
		if (pid == 0) // Child process
		{
			if (i > 0) // Not the first command
				dup2(pipe_fd[0], STDIN_FILENO); // Take input from previous pipe
			if (i < cmd->pipe_count - 1) // Not the last command
				dup2(pipe_fd[1], STDOUT_FILENO); // Send output to the next pipe
			close(pipe_fd[0]);
			close(pipe_fd[1]);

			// Execute the command here
			// execve(...);
		}
		else // Parent process
		{
			close(pipe_fd[1]);
			if (i > 0)
				close(pipe_fd[0]);
			waitpid(pid, NULL, 0);
		}
		i++;
	}
}

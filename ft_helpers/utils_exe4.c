/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onevil_x <onevil_x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 00:13:29 by yaboukir          #+#    #+#             */
/*   Updated: 2025/06/05 04:02:02 by onevil_x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

static void	handle_execve_or_exit(char **argv, char *cmd_path)
{
	if (!cmd_path)
	{
		perror("execve");
		ft_free_split(argv);
		exit(127);
	}
	execve(cmd_path, argv, *get_env());
	perror("execve");
	free(cmd_path);
	ft_free_split(argv);
	exit(127);
}

static void setup_child_fds(t_cmd *cmd, int prev_fd, int *pipe_fd)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	if (!handle_redirections(cmd))
		exit(1);
}

void	handle_child_process(t_cmd *cmd, int prev_fd, int *pipe_fd)
{
	char	**argv;
	char	*cmd_path;

	setup_child_fds(cmd, prev_fd, pipe_fd);
	argv = convert_args(cmd->args);
	if (!argv || !argv[0])
	{
		ft_free_split(argv);
		exit(1);
	}
	if (is_builtin(cmd))
	{
		if (execute_builtin(cmd))
			ft_free_split(argv);
		exit(EXIT_SUCCESS);
	}
	cmd_path = find_command_path(argv[0], *get_env());
	handle_execve_or_exit(argv, cmd_path);
}

void	handle_parent_process(t_cmd *cmd, int *prev_fd, int pipe_fd[2])
{
	if (*prev_fd != -1)
	{
		close(*prev_fd);
		*prev_fd = -1;
	}
	if (cmd->next)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
}

int	handling_cmdops(t_cmd *cmd)
{
	if (!handle_heredoc(cmd))
		return (0);
	if (!handle_redirections(cmd))
		return (0);
	if (!handle_append(cmd))
		return (0);
	return (1);
}

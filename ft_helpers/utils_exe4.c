/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 00:13:29 by yaboukir          #+#    #+#             */
/*   Updated: 2025/05/20 17:50:12 by yaboukir         ###   ########.fr       */
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

static void	setup_child_fds(t_cmd *cmd, int prev_fd, int *pipe_fd)
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
	if (execute_builtin(cmd))
	{
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

void	handling_cmdops(t_cmd *cmd)
{
	(void) cmd;
	handle_heredoc(cmd);
	remove_heredoc_tokens(cmd);
	handle_redirections(cmd);
	handle_append(cmd);
}

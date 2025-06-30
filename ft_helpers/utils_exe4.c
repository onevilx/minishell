/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 00:13:29 by yaboukir          #+#    #+#             */
/*   Updated: 2025/06/30 18:10:14 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

static void	handle_execve_or_exit(char **argv, char *cmd_path)
{
	if (!cmd_path)
	{
		perror("execve");
		exit(127);
	}
	execve(cmd_path, argv, *get_env());
	perror("execve");
	free(cmd_path);
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
	int		ret;

	reset_signal();
	if (!handling_cmdops(cmd))
		exit(1);
	setup_child_fds(cmd, prev_fd, pipe_fd);
	argv = convert_args(cmd->args);
	if (!argv || !argv[0])
	{
		ft_free_split(argv);
		exit(1);
	}
	if (is_builtin(cmd))
	{
		if (ft_strcmp(argv[0], "exit") == 0)
			ret = builtin_exit(cmd->args, 0);
		else
			ret = execute_builtin(cmd);
		ft_free_split(argv);
		exit(ret);
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
	return (handle_redirections_in_order(cmd));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:43:23 by yaboukir          #+#    #+#             */
/*   Updated: 2025/06/29 21:15:30 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

static void	child_exec(t_cmd *cmd)
{
	char	**args_array;

	reset_signal();
	args_array = args_to_array(cmd->args);
	if (!args_array)
		exit(1);
	if (ft_strchr(cmd->args->value, '/'))
		exec_direct_path(cmd, args_array);
	try_exec_paths(cmd);
	exit(127);
}

static void	parent_wait(pid_t pid)
{
	int	status;

	ignore_signal();
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		*get_exit_status() = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		*get_exit_status() = 128 + WTERMSIG(status);
	else
		*get_exit_status() = 1;
	reset_init_signals();
}

int	execute_external(t_cmd *cmd)
{
	pid_t	pid;

	if (!cmd->args || !cmd->args->value)
		return (0);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 0);
	else if (pid == 0)
		child_exec(cmd);
	else
		parent_wait(pid);
	return (1);
}

static void	execute_single_cmd(t_cmd *cmd)
{
	if (is_builtin(cmd))
		*get_exit_status() = execute_builtin(cmd);
	else
		execute_external(cmd);
}

int	execute_command(t_cmd *cmd)
{
	int	stdin_copy;
	int	stdout_copy;

	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	if (!sanitize_all_args(cmd))
	{
		*get_exit_status() = 1;
		dup2(stdin_copy, STDIN_FILENO);
		dup2(stdout_copy, STDOUT_FILENO);
		close(stdin_copy);
		close(stdout_copy);
		cleanup_cmdops_files(cmd);
		return (*get_exit_status());
	}
	if (cmd->next)
		handle_pipe(cmd);
	else
		execute_single_cmd(cmd);
	dup2(stdin_copy, STDIN_FILENO);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdin_copy);
	close(stdout_copy);
	cleanup_cmdops_files(cmd);
	return (*get_exit_status());
}

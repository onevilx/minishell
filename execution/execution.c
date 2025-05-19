/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:43:23 by yaboukir          #+#    #+#             */
/*   Updated: 2025/05/19 20:16:34 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

// Helper function to convert linked list of t_arg to char ** (array of strings)
static char	**args_to_array(t_arg *args)
{
	t_arg	*current;
	int		count;
	char	**arr;
	int		i;

	count = 0;
	current = args;
	while (current)
	{
		count++;
		current = current->next;
	}
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	current = args;
	i = 0;
	while (current)
	{
		arr[i] = ft_strdup(current->value);
		current = current->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

// Try executing the command using paths in $PATH
static void	try_exec_paths(t_cmd *cmd)
{
	char	**paths;
	char	*path;
	int		i;
	char	**args_array;

	paths = ft_split(getenv("PATH"), ':');
	if (!paths)
		exit(1);
	args_array = args_to_array(cmd->args);
	if (!args_array)
		exit(1);
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin_free(path, args_array[0]);
		if (access(path, X_OK) == 0)
			execve(path, args_array, *get_env());
		free(path);
		i++;
	}
	free_split(paths);
	printf("minishell: command not found: %s\n", args_array[0]);
	free(args_array);
	exit(127);
}

// Execute external commands
int	execute_external(t_cmd *cmd)
{
	pid_t	pid;
	int		status;
	char	**args_array;

	if (!cmd->args || !cmd->args->value)
		return (0);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 0);
	else if (pid == 0)
	{
		reset_signal();
		args_array = args_to_array(cmd->args);
		if (!args_array)
			exit(1);
		if (access(cmd->args->value, X_OK) == 0)
			execve(cmd->args->value, args_array, *get_env());
		try_exec_paths(cmd);
		free(args_array);
	}
	else
	{
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
	return (1);
}

t_arg	*token_to_args(t_token *start, t_token *end)
{
	t_arg	*head;
	t_arg	*tail;
	t_arg	*new_arg;

	head = NULL;
	tail = NULL;
	while (start && start != end)
	{
		if (start->type == WORD)
		{
			new_arg = malloc(sizeof(t_arg));
			if (!new_arg)
				return (NULL);
			new_arg->value = ft_strdup(start->value);
			new_arg->next = NULL;
			if (!head)
				head = new_arg;
			else
				tail->next = new_arg;
			tail = new_arg;
		}
		start = start->next;
	}
	return (head);
}

int	execute_command(t_cmd *cmd)
{
	int		stdin_copy;
	int		stdout_copy;
	t_cmd	*cur;
	int		exit_status = 0;

	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	cur = cmd;
	while (cur)
	{
		sanitize_args(cur);
		cur = cur->next;
	}
	if (cmd->next)
		handle_pipe(cmd);
	else
	{
		handling_cmdops(cmd);
		if (is_builtin(cmd))
			*get_exit_status() = execute_builtin(cmd);
		else
			execute_external(cmd);
	}
	dup2(stdin_copy, STDIN_FILENO);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdin_copy);
	close(stdout_copy);
	return (exit_status);
}

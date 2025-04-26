/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:43:23 by yaboukir          #+#    #+#             */
/*   Updated: 2025/04/25 18:19:02 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

int	execute_external(char **args)
{
	pid_t	pid;
	int		status;

	if (!args || !args[0])
		return (0);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (0);
	}
	else if (pid == 0) // Child process
	{
		char	*path;
		char	**paths;
		int		i;

		if (access(args[0], X_OK) == 0)
			execve(args[0], args, *get_env());
		paths = ft_split(getenv("PATH"), ':');
		if (!paths)
			exit(1);
		i = 0;
		while (paths[i])
		{
			path = ft_strjoin(paths[i], "/");
			path = ft_strjoin_free(path, args[0]);
			if (access(path, X_OK) == 0)
				execve(path, args, *get_env());
			free(path);
			i++;
		}
		free_split(paths);
		printf("minishell: command not found: %s\n", args[0]);
		exit(127);
	}
	else // Parent process
		waitpid(pid, &status, 0);
	return (1);
}

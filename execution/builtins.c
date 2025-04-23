/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:14:27 by yaboukir          #+#    #+#             */
/*   Updated: 2025/04/22 22:29:53 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

static void	handle_builtin(char **args)
{
	if (ft_strcmp(args[0], "echo") == 0)
		builtin_echo(args);
	else if (ft_strcmp(args[0], "cd") == 0)
		builtin_cd(args);
	else if (ft_strcmp(args[0], "pwd") == 0)
		builtin_pwd(args);
	else if (ft_strcmp(args[0], "export") == 0)
		builtin_export(args);
	else if (ft_strcmp(args[0], "unset") == 0)
		builtin_unset(args);
	else if (ft_strcmp(args[0], "env") == 0)
		builtin_env(args);
	else if (ft_strcmp(args[0], "exit") == 0)
		builtin_exit(args);
}

int	execute_builtin(char **args)
{
	if (is_builtin(args[0]))
	{
		handle_builtin(args);
		return (1);
	}
	return (0);
}

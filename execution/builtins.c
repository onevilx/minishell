/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:14:27 by yaboukir          #+#    #+#             */
/*   Updated: 2025/06/24 00:19:08 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

int	is_builtin(t_cmd *cmd)
{
	if (cmd->args == NULL || cmd->args->value == NULL)
		return (0);
	if (ft_strcmp(cmd->args->value, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd->args->value, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd->args->value, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd->args->value, "export") == 0)
		return (1);
	if (ft_strcmp(cmd->args->value, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd->args->value, "env") == 0)
		return (1);
	if (ft_strcmp(cmd->args->value, "exit") == 0)
		return (1);
	return (0);
}

static int	handle_builtin(t_cmd *cmd)
{
	if (ft_strcmp(cmd->args->value, "echo") == 0)
		return (builtin_echo(cmd->args));
	else if (ft_strcmp(cmd->args->value, "cd") == 0)
		return (builtin_cd(cmd->args));
	else if (ft_strcmp(cmd->args->value, "pwd") == 0)
		return (builtin_pwd(cmd->args));
	else if (ft_strcmp(cmd->args->value, "export") == 0)
		return (builtin_export(cmd->args));
	else if (ft_strcmp(cmd->args->value, "unset") == 0)
		return (builtin_unset(cmd->args));
	else if (ft_strcmp(cmd->args->value, "env") == 0)
		return (builtin_env(cmd->args));
	else if (ft_strcmp(cmd->args->value, "exit") == 0)
		return (builtin_exit(cmd->args));
	return (0);
}

int	execute_builtin(t_cmd *cmd)
{
	if (is_builtin(cmd))
		return (handle_builtin(cmd));
	return (0);
}

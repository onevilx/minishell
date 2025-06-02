/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onevil_x <onevil_x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:14:27 by yaboukir          #+#    #+#             */
/*   Updated: 2025/06/02 18:03:46 by onevil_x         ###   ########.fr       */
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
		builtin_echo(cmd->args);
	else if (ft_strcmp(cmd->args->value, "cd") == 0)
		builtin_cd(cmd->args);
	else if (ft_strcmp(cmd->args->value, "pwd") == 0)
		builtin_pwd(cmd->args);
	else if (ft_strcmp(cmd->args->value, "export") == 0)
		builtin_export(cmd->args);
	else if (ft_strcmp(cmd->args->value, "unset") == 0)
		builtin_unset(cmd->args);
	else if (ft_strcmp(cmd->args->value, "env") == 0)
		builtin_env(cmd->args);
	else if (ft_strcmp(cmd->args->value, "exit") == 0)
		builtin_exit(cmd->args);
	return (1);
}

int	execute_builtin(t_cmd *cmd)
{
	if (is_builtin(cmd))
		handle_builtin(cmd);
	return (0);
}

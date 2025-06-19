/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe11.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 20:33:33 by yaboukir          #+#    #+#             */
/*   Updated: 2025/06/19 20:35:04 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

void	free_args_list(t_arg *args)
{
	t_arg	*tmp;

	while (args)
	{
		tmp = args->next;
		free(args->value);
		free(args);
		args = tmp;
	}
}

void cleanup_cmd(t_cmd *cmd)
{
	while (cmd)
	{
		free_args_list(cmd->args);
		cmd->args = NULL;
		cmd = cmd->next;
	}
}

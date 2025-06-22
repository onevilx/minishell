/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 00:48:22 by yaboukir          #+#    #+#             */
/*   Updated: 2025/06/22 00:33:05 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

int	do_append_fd(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("minishell: open (append redirection)");
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	do_append_redirection(t_token *curr)
{
	if (!curr->next)
	{
		write(2,
			"minishell: syntax error near unexpected token `newline'\n", 55);
		return (0);
	}
	return (do_append_fd(curr->next->value) == 0);
}

int	is_valid_n_flag(char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (0);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

t_arg	*check_n_flag(t_arg *args, int *no_newline)
{
	t_arg	*current;

	current = args->next;
	*no_newline = 0;
	while (current && current->value && current->value[0] == '\0')
		current = current->next;
	while (current && is_valid_n_flag(current->value))
	{
		*no_newline = 1;
		current = current->next;
	}
	return (current);
}

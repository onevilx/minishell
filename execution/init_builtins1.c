/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_builtins1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:40:00 by yaboukir          #+#    #+#             */
/*   Updated: 2025/06/25 01:18:40 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

int	builtin_echo(t_arg *args)
{
	int		no_newline;
	t_arg	*current;
	int		first;

	first = 1;
	current = check_n_flag(args, &no_newline);
	while (current)
	{
		if (!first)
			write(STDOUT_FILENO, " ", 1);
		write(STDOUT_FILENO, current->value, ft_strlen(current->value));
		first = 0;
		current = current->next;
	}
	if (!no_newline)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}

int	builtin_cd(t_arg *args)
{
	char	*home;
	char	*oldpwd;
	t_arg	*current;

	current = args->next;
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		oldpwd = ft_strdup("");
	if (!current)
	{
		home = get_env_value("HOME");
		if (!home || chdir(home) != 0)
			return (free(oldpwd), perror("cd"), 1);
	}
	else if (current && current->next)
		return (write(2, "cd: too many arguments\n", 24), 1);
	else if (chdir(current->value) != 0)
		return (perror("cd"), 1);
	update_pwd_vars(oldpwd);
	free(oldpwd);
	return (0);
}

int	builtin_pwd(t_arg *args)
{
	char	*cwd;

	(void) args;
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		write(STDOUT_FILENO, cwd, ft_strlen(cwd));
		write(STDOUT_FILENO, "\n", 1);
		free(cwd);
		return (0);
	}
	perror("pwd");
	return (1);
}

static int	is_numeric(const char *str)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	if (!str || !str[0])
		return (0);
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!str[i])
		return (0);
	return (is_digit_str(str, i, sign));
}

int	builtin_exit(t_arg *args, int print_exit)
{
	t_arg	*arg;
	int		exit_status;

	if (print_exit)
		write(1, "exit\n", 5);
	arg = args->next;
	if (!arg)
		exit_status = 0;
	else if (!is_numeric(arg->value))
	{
		write(2, "exit: numeric argument required\n", 32);
		exit_status = 255;
	}
	else if (arg->next)
	{
		write(2, "exit: too many arguments\n", 25);
		*get_exit_status() = 1;
		return (1);
	}
	else
		exit_status = ft_atoi(arg->value);
	*get_exit_status() = exit_status;
	return (exit_status);
}

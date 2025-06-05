/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_builtins1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onevil_x <onevil_x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:40:00 by yaboukir          #+#    #+#             */
/*   Updated: 2025/06/05 14:59:03 by onevil_x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

int	builtin_echo(t_arg *args)
{
	int		no_newline;
	t_arg	*current;

	current = check_n_flag(args, &no_newline);
	while (current)
	{
		printf("%s", current->value);
		if (current->next)
			printf(" ");
		current = current->next;
	}
	if (!no_newline)
		printf("\n");
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
		return (free(oldpwd), write(2, "cd: too many arguments\n", 24), 1);
	else if (chdir(current->value) != 0)
		return (free(oldpwd), perror("cd"), 1);
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

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(t_arg *args)
{
	t_arg	*current;
	int		exit_status;

	current = args->next;
	write(1, "exit\n", 5);
	if (!current)
		exit(0);
	if (current && !current->next)
	{
		if (is_numeric(current->value))
		{
			exit_status = ft_atoi(current->value);
			exit(exit_status);
		}
		else
		{
			write(2, "exit: numeric argument required\n", 32);
			exit(2);
		}
	}
	write(2, "exit: too many arguments\n", 25);
	return (1);
}

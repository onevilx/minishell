/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_builtins1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:40:00 by yaboukir          #+#    #+#             */
/*   Updated: 2025/05/20 16:51:59 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

void	builtin_echo(t_arg *args)
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
}

// CD command
void	builtin_cd(t_arg *args)
{
	char	*path;
	t_arg	*current;

	current = args->next;
	if (!current)
	{
		path = get_env_value("HOME");
		if (!path || chdir(path) != 0)
			perror("cd");
	}
	else if (current && !current->next)
	{
		if (chdir(current->value) != 0)
			perror("cd");
	}
	else
		write(2, "cd: too many arguments\n", 24);
}

// PWD command
void	builtin_pwd(t_arg *args)
{
	char	*cwd;

	(void) args;
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		write(STDOUT_FILENO, cwd, ft_strlen(cwd));
		write(STDOUT_FILENO, "\n", 1);
		free(cwd);
	}
	else
		perror("pwd");
}

// Helper function to check if a string is numeric (for exit)
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

void	builtin_exit(t_arg *args)
{
	t_arg	*current;
	int		exit_status;

	current = args->next;
	if (!current)
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	if (current && !current->next)
	{
		if (is_numeric(current->value))
		{
			exit_status = ft_atoi(current->value);
			write(1, "exit\n", 5);
			exit(exit_status);
		}
		else
		{
			write(2, "exit: numeric argument required\n", 32);
			exit(2);
		}
	}
	write(2, "exit: too many arguments\n", 25);
}

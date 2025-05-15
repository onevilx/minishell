/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_builtins1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:40:00 by yaboukir          #+#    #+#             */
/*   Updated: 2025/05/14 19:28:07 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

void	builtin_echo(t_arg *args)
{
	int		no_newline;
	t_arg	*current;

	current = args->next;
	no_newline = 0;
	while (current && current->value && ft_strncmp(current->value, "-n", 2) == 0)
	{
		int i = 2;
		while (current->value[i] == 'n')
			i++;
		if (current->value[i] != '\0')
			break;
		no_newline = 1;
		current = current->next;
	}
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

	current = args->next; // Skip the "cd" command itself

	if (!current) // No argument given
	{
		path = get_env_value("HOME");
		if (!path || chdir(path) != 0)
			perror("cd");
	}
	else if (current && !current->next) // Single argument
	{
		if (chdir(current->value) != 0)
			perror("cd");
	}
	else // More than one argument
	{
		write(2, "cd: too many arguments\n", 24);
	}
}


// PWD command
void	builtin_pwd(t_arg *args)
{
	char	*cwd;

	(void) args;  // args are unused
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
	exit_status = 0;
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
			return;
		}
	}
	write(2, "exit: too many arguments\n", 25);
}


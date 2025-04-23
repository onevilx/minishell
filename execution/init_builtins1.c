/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_builtins1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:40:00 by yaboukir          #+#    #+#             */
/*   Updated: 2025/04/23 00:22:19 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	builtin_echo(char **args)
{
	int	i;
	int	no_newline;

	i = 1;
	no_newline = 0;
	if (args[i] && ft_strcmp(args[i], "-n") == 0)
	{
		no_newline = 1;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!no_newline)
		printf("\n");
}

void	builtin_cd(char **args)
{
	if (args[1] == NULL)
		return ;
	if (chdir(args[1]) != 0)
		perror("cd");
}

void	builtin_pwd(char **args)
{
	char	*cwd;

	(void) args;
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		write(1, cwd, ft_strlen(cwd));
		write(1, "\n", 1);
		free(cwd);
	}
	else
		perror("pwd");
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

void	builtin_exit(char **args)
{
	write(1, "exit\n", 5);
	if (!args[1])
		exit(0);
	if (!is_numeric(args[1]))
	{
		write(2, "exit: numeric argument required\n", 32);
		exit(255);
	}
	if (args[2])
	{
		write(2, "exit: too many arguments\n", 25);
		return ;
	}
	exit(ft_atoi(args[1]) % 256);
}

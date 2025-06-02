/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_builtins3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onevil_x <onevil_x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:20:00 by yaboukir          #+#    #+#             */
/*   Updated: 2025/06/02 18:57:51 by onevil_x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

static int	is_valid_key(char *key)
{
	int	i;

	if (!key || !key[0])
		return (0);
	i = 0;
	while (key[i])
	{
		if (!(key[i] == '_' || (key[i] >= 'A' && key[i] <= 'Z')
				|| (key[i] >= 'a' && key[i] <= 'z')
				|| (i > 0 && key[i] >= '0' && key[i] <= '9')))
			return (0);
		i++;
	}
	return (1);
}

// Remove an environment variable by its key
static void	remove_env_var(char *key)
{
	int		i;
	int		j;
	char	**env;
	char	**new_env;

	env = *get_env();
	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * i);
	if (!new_env)
		return ;
	i = -1;
	j = 0;
	while (env[++i])
	{
		if (ft_strncmp(env[i], key, ft_strlen(key))
			|| env[i][ft_strlen(key)] != '=')
			new_env[j++] = env[i];
		else
			free(env[i]);
	}
	new_env[j] = NULL;
	free(env);
	*get_env() = new_env;
}

void	builtin_unset(t_arg *args)
{
	t_arg	*current;

	current = args->next;
	while (current)
	{
		if (is_valid_key(current->value))
			remove_env_var(current->value);
		else
			write(2, "unset: not a valid identifier\n", 31);
		current = current->next;
	}
}

// Print all environment variables
static void	print_env(void)
{
	int		i;
	char	**env;

	env = *get_env();
	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		write(1, env[i], ft_strlen(env[i]));
		write(1, "\n", 1);
		i++;
	}
}

void	builtin_env(t_arg *args)
{
	t_arg	*current;
	char	*path;
	char	**envp;

	current = args->next;
	if (!current)
		print_env();
	else
	{
		path = current->value;
		envp = *get_env();
		if (fork() == 0)
		{
			if (execve(path, (char **)(current->next), envp) == -1)
			{
				write(2, "env: command not found\n", 23);
				exit(1);
			}
		}
		wait(NULL);
	}
}

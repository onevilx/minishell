/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_builtins2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:53:54 by yaboukir          #+#    #+#             */
/*   Updated: 2025/05/14 19:08:02 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

// Check if the export argument is valid (contains a key-value pair)
static int	is_valid_export(char *arg)
{
	int	i;

	if (!arg || !arg[0] || arg[0] == '=')
		return (0);
	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (!(arg[i] == '_' || (arg[i] >= 'A' && arg[i] <= 'Z')
				|| (arg[i] >= 'a' && arg[i] <= 'z')
				|| (i > 0 && arg[i] >= '0' && arg[i] <= '9')))
			return (0);
		i++;
	}
	return (1);
}

// Add a new environment variable
static void	add_env_var(char *arg)
{
	char	**env;
	char	**new_env;
	int		i;

	env = *get_env();
	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return ;
	i = -1;
	while (env[++i])
		new_env[i] = env[i];
	new_env[i++] = ft_strdup(arg);
	new_env[i] = NULL;
	free(env);
	*get_env() = new_env;
}

// Print all exported variables in the format 'declare -x key=value'
static void	print_export_vars(void)
{
	char	**env;
	int		i;

	env = *get_env();
	i = 0;
	while (env[i])
	{
		write(1, "declare -x ", 11);
		write(1, env[i], ft_strlen(env[i]));
		write(1, "\n", 1);
		i++;
	}
}

// Handle each export argument, ensuring it's valid and add it to the environment
static void	handle_export_arg(t_arg *arg)
{
	char	*key;
	char	**env;
	int		idx;
	int		pos;

	if (!is_valid_export(arg->value))
		return ((void)write(2, "export: not a valid identifier\n", 31));
	pos = 0;
	while (arg->value[pos] && arg->value[pos] != '=')
		pos++;
	if (pos == 0)
		return ((void)write(2, "export: not a valid identifier\n", 31));
	key = ft_substr(arg->value, 0, pos);
	env = *get_env();
	idx = find_env_index(env, key);
	free(key);
	if (idx >= 0)
		update_env_var(idx, arg->value);
	else
		add_env_var(arg->value);
}

// Builtin export command
void	builtin_export(t_arg *args)
{
	t_arg	*current;

	if (!args || args->next == NULL) // Fix: also check if there are no arguments after "export"
		return (print_export_vars());
	current = args->next;  // Skip the command itself
	while (current)
	{
		handle_export_arg(current);
		current = current->next;
	}
}

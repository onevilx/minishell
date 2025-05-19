/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_builtins2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:53:54 by yaboukir          #+#    #+#             */
/*   Updated: 2025/05/19 18:53:42 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

char	***get_export_list(void)
{
	static char	**export_list = NULL;

	return (&export_list);
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

// Main print_export_vars function
static void	print_export_vars(void)
{
	char	**env;
	char	**export;

	env = *get_env();
	export = *get_export_list();
	print_export_only_vars(export);
	print_env_vars(env);
}

static void	handle_export_arg(t_arg *arg)
{
	char	*key;
	char	**env;
	char	**export_list;
	int		idx;
	int		pos;

	if (!is_valid_export(arg->value))
		return ((void)write(2, "export: not a valid identifier\n", 31));
	pos = 0;
	while (arg->value[pos] && arg->value[pos] != '=')
		pos++;
	key = ft_substr(arg->value, 0, pos);
	env = *get_env();
	export_list = *get_export_list();
	if (!str_in_array(export_list, key))
		add_to_array(get_export_list(), key);
	if (arg->value[pos] == '=')
	{
		idx = find_env_index(env, key);
		if (idx >= 0)
			update_env_var(idx, arg->value);
		else
			add_env_var(arg->value);
	}
	free(key);
}

// Builtin export command
void	builtin_export(t_arg *args)
{
	t_arg	*current;

	if (!args || args->next == NULL)
		return (print_export_vars());
	current = args->next;
	while (current)
	{
		handle_export_arg(current);
		current = current->next;
	}
}

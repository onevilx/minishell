/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_builtins2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:53:54 by yaboukir          #+#    #+#             */
/*   Updated: 2025/05/23 19:43:03 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

char	***get_export_list(void)
{
	static char	**export_list = NULL;

	return (&export_list);
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

static void	add_to_export_list(char *key)
{
	char	**export_list;

	export_list = *get_export_list();
	if (!str_in_array(export_list, key))
		add_to_array(get_export_list(), key);
}

void	handle_export_arg(t_arg *arg)
{
	char	*key;
	int		append;
	int		pos;

	if (!is_valid_export(arg->value))
		return ((void)write(2, "export: not a valid identifier\n", 31));
	append = is_append_mode(arg->value, &pos);
	key = ft_substr(arg->value, 0, pos);
	add_to_export_list(key);
	handle_export_logic(arg, key, append, pos);
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

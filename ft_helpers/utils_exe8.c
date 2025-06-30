/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe8.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:46:01 by yaboukir          #+#    #+#             */
/*   Updated: 2025/06/30 23:22:12 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

int	str_in_array(char **arr, char *str)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		if (!ft_strcmp(arr[i], str))
			return (1);
		i++;
	}
	return (0);
}

void	add_to_array(char ***arr_ptr, char *str)
{
	int		i;
	int		j;
	char	**arr;
	char	**new_arr;

	i = 0;
	arr = *arr_ptr;
	while (arr && arr[i])
		i++;
	new_arr = g_malloc(sizeof(char *) * (i + 2));
	if (!new_arr)
		return ;
	j = 0;
	while (j < i)
	{
		new_arr[j] = arr[j];
		j++;
	}
	new_arr[i] = ft_strdup(str);
	new_arr[i + 1] = NULL;
	free(arr);
	*arr_ptr = new_arr;
}

int	is_valid_export(char *arg)
{
	int	i;

	i = 0;
	if (!arg || !arg[0] || arg[0] == '=')
		return (0);
	while (arg[i] && arg[i] != '=' && !(arg[i] == '+' && arg[i + 1] == '='))
	{
		if (!(arg[i] == '_' || (arg[i] >= 'A' && arg[i] <= 'Z')
				|| (arg[i] >= 'a' && arg[i] <= 'z')
				|| (i > 0 && arg[i] >= '0' && arg[i] <= '9')))
			return (0);
		i++;
	}
	return (1);
}

void	print_export_only_vars(char **export)
{
	int		i;

	i = 0;
	while (export && export[i])
	{
		if (!get_env_value(export[i]))
		{
			write(1, "declare -x ", 11);
			write(1, export[i], ft_strlen(export[i]));
			write(1, "\n", 1);
		}
		i++;
	}
}

void	print_env_vars(char **env)
{
	int		i;
	char	*equal_pos;

	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp(env[i], "_=", 2) == 0)
		{
			i++;
			continue ;
		}
		equal_pos = ft_strchr(env[i], '=');
		write(1, "declare -x ", 11);
		if (equal_pos)
		{
			write(1, env[i], equal_pos - env[i]);
			write(1, "=\"", 2);
			write(1, equal_pos + 1, ft_strlen(equal_pos + 1));
			write(1, "\"", 1);
		}
		else
			write(1, env[i], ft_strlen(env[i]));
		write(1, "\n", 1);
		i++;
	}
}

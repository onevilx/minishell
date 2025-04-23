/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:32:02 by yaboukir          #+#    #+#             */
/*   Updated: 2025/04/23 00:00:31 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

char	***get_env(void)
{
	static char	**env = NULL;

	return (&env);
}

void	init_env(char **envp)
{
	char	**new_env;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return ;
	i = -1;
	while (envp[++i])
		new_env[i] = ft_strdup(envp[i]);
	new_env[i] = NULL;
	*get_env() = new_env;
}

int	open_tmpfile(void)
{
	return (open("/tmp/heredoc_input.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644));
}

void	write_line(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

void	read_input(int fd, char *delimiter)
{
	char	*line;
	while ((line = readline("> ")) != NULL)
	{
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		write_line(fd, line);
		free(line);
	}
	free(line);
}


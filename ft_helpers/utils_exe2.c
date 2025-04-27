/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:32:02 by yaboukir          #+#    #+#             */
/*   Updated: 2025/04/27 17:33:38 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

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

	line = readline("> ");
	while (line != NULL)
	{
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		write_line(fd, line);
		free(line);
	}
	free(line);
}

void	free_split(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*joined;

	if (!s1 || !s2)
		return (NULL);
	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}

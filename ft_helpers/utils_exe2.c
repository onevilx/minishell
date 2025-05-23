/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 23:32:02 by yaboukir          #+#    #+#             */
/*   Updated: 2025/05/23 20:01:52 by yaboukir         ###   ########.fr       */
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

char	*read_input(const char *delimiter)
{
	char	*line;
	char	*buffer;
	char	*tmp;

	buffer = ft_strdup("");
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
			break ;
		tmp = ft_strjoin(buffer, line);
		free(buffer);
		buffer = tmp;
		buffer = ft_strjoin(buffer, "\n");
		free(line);
	}
	free(line);
	return (buffer);
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

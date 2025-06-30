/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_funcs5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:30:43 by yaboukir          #+#    #+#             */
/*   Updated: 2025/06/30 18:26:44 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (needle[0] == 0)
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		while (haystack [i + j] == needle[j] && haystack [i + j] && i + j < len)
		{
			j++;
			if (needle [j] == 0)
				return ((char *) haystack + i);
		}
		i++;
		j = 0;
	}
	return (0);
}

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, s3);
	return (res);
}

void	*ft_free(char **arr, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (arr[i])
			free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

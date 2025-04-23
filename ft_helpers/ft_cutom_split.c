/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cutom_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:29:45 by obouftou          #+#    #+#             */
/*   Updated: 2025/04/23 15:24:25 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniheader.h"

static void	*ft_free(char **arr, int count)
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

static size_t	get_len(char const *s, char c)
{
	if (strchr(s, c))
		return (strchr(s, c) - s);
	return (ft_strlen(s));
}

static size_t	ft_countword(char const *s, char c)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	len;
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	arr = ft_calloc((ft_countword(s, c) + 1), sizeof(char *));
	if (arr == NULL)
		return (NULL);
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			len = get_len(s, c);
			arr[i] = ft_substr(s, 0, len);
			if (arr[i] == NULL)
				return (ft_free(arr, i));
			s = s + len;
			i++;
		}
	}
	return (arr);
}

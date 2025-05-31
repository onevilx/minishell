/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_costum_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onevil_x <onevil_x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:53:01 by yaboukir          #+#    #+#             */
/*   Updated: 2025/05/31 20:10:22 by onevil_x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

static char	*ft_substr1(const char *s, unsigned int start, size_t len)
{
	char	*s1;
	size_t	i;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	i = 0;
	if (slen <= start)
		return (ft_strdup(""));
	if (start + len > slen)
		len = slen - start;
	s1 = malloc((len + 1));
	if (s1 == NULL)
		return (NULL);
	while (i < len)
	{
		s1[i] = s[start + i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

static void	*ft_calloc1(size_t count, size_t size)
{
	unsigned char	*tmp;

	tmp = malloc(count * size);
	if (!tmp)
		return (0);
	ft_bzero(tmp, count * size);
	return (tmp);
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

char	**ft_split_once(const char *s, char c)
{
	char	**result;
	char	*sep;
	size_t	len;

	if (!s)
		return (NULL);
	result = ft_calloc1(3, sizeof(char *));
	if (!result)
		return (NULL);
	sep = strchr(s, c);
	if (!sep)
	{
		result[0] = ft_substr(s, 0, strlen(s));
		return (result);
	}
	len = sep - s;
	result[0] = ft_substr1(s, 0, len);
	result[1] = ft_substr1(s, len + 1, strlen(s) - len - 1);
	if (!result[0] || !result[1])
		return (ft_free(result, 2));
	return (result);
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

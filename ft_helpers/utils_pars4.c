/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_parc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:54:42 by obouftou          #+#    #+#             */
/*   Updated: 2025/04/23 15:26:14 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"



char	*ft_strdup(const char *s1)
{
	char	*tmp;
	size_t	i;

	i = 0;
	tmp = (char *)malloc(ft_strlen(s1) + 1);
	if (tmp == NULL)
		return (NULL);
	while (s1[i])
	{
		tmp[i] = s1[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char *strndup(const char *s, size_t n)
{
	size_t i;
	char *dup;

	dup = malloc(n + 1);
	if (!dup)
		return NULL;

	for (i = 0; i < n && s[i]; i++)
		dup[i] = s[i];

	dup[i] = '\0';
	return dup;
}

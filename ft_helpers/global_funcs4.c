/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_funcs4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:34:27 by yaboukir          #+#    #+#             */
/*   Updated: 2025/06/29 02:52:51 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

int	ft_isalpha(int x)
{
	if ((x >= 'A' && x <= 'Z' ) || (x >= 'a' && x <= 'z'))
		return (1);
	return (0);
}

int	ft_isalnum(int x)
{
	if ((x >= 'A' && x <= 'Z')
		|| (x >= 'a' && x <= 'z')
		|| (x >= '0' && x <= '9'))
		return (1);
	return (0);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	if (n <= 0)
		return ;
	while (n > 0)
	{
		*(p) = 0;
		p++;
		n--;
	}
}

size_t	get_len(char const *s, char c)
{
	if (ft_strchr(s, c))
		return (ft_strchr(s, c) - s);
	return (ft_strlen(s));
}

int	*get_exit_status(void)
{
	static int	status = 0;

	return (&status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_funcs3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onevil_x <onevil_x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:59:36 by yaboukir          #+#    #+#             */
/*   Updated: 2025/05/18 04:27:16 by onevil_x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

static size_t	int_len(int nb)
{
	size_t	count;

	count = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		count = 1;
		nb = -nb;
	}
	while (nb != 0)
	{
		nb /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long int	nb;
	size_t		len;
	char		*str;

	nb = n;
	if (nb == -2147483648)
		return (ft_strdup("-2147483648"));
	len = int_len(nb) + 1;
	str = malloc(len);
	if (!str)
		return (NULL);
	str[len - 1] = '\0';
	if (nb == 0)
		str[0] = '0';
	else if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	while (nb)
	{
		str[--len - 1] = (nb % 10) + '0';
		nb = nb / 10;
	}
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	char			y;

	y = (char) c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == y)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == y)
		return ((char *) &s[i]);
	return (NULL);
}

void	print_welcome(void)
{
	printf("🟢 Welcome to \033[1;32mminishell\033[0m, ");
	printf("this project built by pinky and the brain!\n");
}

void	ft_launching(void)
{
	init_terminal();
	print_welcome();
}

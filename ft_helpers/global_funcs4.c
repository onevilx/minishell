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

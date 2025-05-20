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

static void	*ft_free(char **arr, int count)
{
	int	i = 0;
	while (i < count)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
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
		return result;
	}
	len = sep - s;
	result[0] = ft_substr1(s, 0, len);
	result[1] = ft_substr1(s, len + 1, strlen(s) - len - 1);
	if (!result[0] || !result[1])
		return (ft_free(result, 2));
	return result;
}

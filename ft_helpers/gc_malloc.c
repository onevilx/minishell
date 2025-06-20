#include "../includes/protos.h"
void	*g_malloc(size_t size)
{
	static t_gc	*list = NULL;
	void		*ptr;
	t_gc		*node;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);

	node = malloc(sizeof(t_gc));
	if (!node)
		return (free(ptr), NULL);

	node->ptr = ptr;
	node->next = list;
	list = node;

	return (ptr);
}

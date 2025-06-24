/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:31:16 by yaboukir          #+#    #+#             */
/*   Updated: 2025/06/24 17:50:19 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

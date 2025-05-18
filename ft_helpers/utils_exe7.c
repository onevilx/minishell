/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe7.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onevil_x <onevil_x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 00:58:58 by yaboukir          #+#    #+#             */
/*   Updated: 2025/05/18 05:32:33 by onevil_x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

void	free_redirections(t_redirect *redir)
{
	t_redirect	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->val);
		free(redir);
		redir = tmp;
	}
}

void	free_tokensexe(t_token **tokens)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]->value);
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

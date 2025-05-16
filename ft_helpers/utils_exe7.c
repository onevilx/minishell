/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe7.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 00:58:58 by yaboukir          #+#    #+#             */
/*   Updated: 2025/05/16 01:42:19 by yaboukir         ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouftou <obouftou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:54:42 by obouftou          #+#    #+#             */
/*   Updated: 2025/06/18 17:51:03 by obouftou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

int	is_redirection(t_token *tok)
{
	return (tok->type == REDIR_IN || tok->type == REDIR_OUT
		|| tok->type == APPEND || tok->type == HEREDOC);
}

int	handle_redirection(t_cmd *cmd, t_token **cur, t_token **args, int *i)
{
	(void) args;
	(void) i;
	if (!(*cur)->next || (*cur)->next->type != WORD)
		return (0);
	cmd->red = add_redirect(cmd->red, (*cur)->type,
			ft_strdup((*cur)->next->value));
	*cur = (*cur)->next->next;
	return (1);
}

void	save_word(t_token *cur, t_token **args, int *i)
{
	if (cur->type == WORD)
		args[(*i)++] = cur;
}

int	parse_commands_loop(t_token *tokens, t_cmd **head,
				t_cmd **last, int total_pipes)
{
	t_token	*start;
	t_token	*end;
	t_cmd	*cmd;

	start = tokens;
	while (start)
	{
		end = start;
		while (end && end->type != PIPE)
			end = end->next;
		cmd = parse_command_node(start, end);
		if (!cmd)
			return (free_command_list(*head), 0);
		cmd->pipe_count = total_pipes;
		if (!*head)
			*head = cmd;
		else
			(*last)->next = cmd;
		*last = cmd;
		start = get_next_command_tokens(end);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouftou <obouftou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:57:06 by obouftou          #+#    #+#             */
/*   Updated: 2025/06/27 00:14:05 by obouftou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

t_token	*get_next_command_tokens(t_token *cur)
{
	while (cur && cur->type != PIPE)
		cur = cur->next;
	if (cur)
		return (cur->next);
	return (NULL);
}

static void	init_command(t_cmd **cmd)
{
	*cmd = g_malloc(sizeof(t_cmd));
	if (!*cmd)
		return ;
	(*cmd)->pipe_count = 0;
	(*cmd)->red = NULL;
	(*cmd)->token = NULL;
	(*cmd)->next = NULL;
}

int	fill_command_data(t_cmd *cmd, t_token *start, t_token *end)
{
	t_token	**args;
	t_token	*cur;
	int		i;

	i = 0;
	cur = start;
	args = g_malloc(sizeof(t_token *) * 1024);
	if (!args)
		return (0);
	while (cur && cur != end)
	{
		if (is_redirection(cur))
		{
			if (!handle_redirection1(cmd, &cur, args, &i))
				return (free(args), 0);
			continue ;
		}
		save_word(cur, args, &i);
		cur = cur->next;
	}
	args[i] = NULL;
	cmd->token = args;
	return (1);
}

t_cmd	*parse_command_node(t_token *start, t_token *end)
{
	t_cmd	*cmd;

	init_command(&cmd);
	if (!cmd)
		return (NULL);
	cmd->args = token_to_args(start, end);
	if (!cmd->args)
	{
		free(cmd->args);
		return (NULL);
	}
	if (!fill_command_data(cmd, start, end))
	{
		return (NULL);
	}
	return (cmd);
}

t_cmd	*ft_parse_commands(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*last;
	int		total_pipes;

	init_for_norm(&head, &last, &total_pipes, tokens);
	if (!parse_commands_loop(tokens, &head, &last, total_pipes))
		return (NULL);
	return (head);
}

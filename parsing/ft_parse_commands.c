/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:57:06 by obouftou          #+#    #+#             */
/*   Updated: 2025/05/14 16:32:40 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

/* Helper to move to next command tokens after a pipe */
static t_token *get_next_command_tokens(t_token *cur)
{
	while (cur && cur->type != PIPE)
		cur = cur->next;
	if (cur)
		return cur->next;
	return NULL;
}

/* Initialize command structure */
static void init_command(t_cmd **cmd)
{
	*cmd = malloc(sizeof(t_cmd));
	if (!*cmd)
		return;
	(*cmd)->pipe_count = 0;
	(*cmd)->red = NULL;
	(*cmd)->token = NULL;
	(*cmd)->next = NULL;
}

/* Fill command with tokens and redirections */
static int fill_command_data(t_cmd *cmd, t_token *start, t_token *end)
{
	t_token **args;
	t_token *cur;
	int i;

	i = 0;
	cur = start;
	args = malloc(sizeof(t_token *) * 1024);
	if (!args)
		return (0);
	while (cur && cur != end)
	{
		if (cur->type == REDIR_IN || cur->type == REDIR_OUT
			|| cur->type == APPEND || cur->type == HEREDOC)
		{
			if (!cur->next || cur->next->type != WORD)
				return (free(args), 0);
			cmd->red = add_redirect(cmd->red, cur->type, strdup(cur->next->value));
			cur = cur->next->next;
			continue;
		}
		if (cur->type == WORD)
			args[i++] = cur;
		cur = cur->next;
	}
	args[i] = NULL;
	cmd->token = args;
	return (1);
}

/* Parse one command node */
static t_cmd *parse_command_node(t_token *start, t_token *end)
{
	t_cmd *cmd;

	init_command(&cmd);
	if (!cmd)
		return NULL;
	cmd->args = token_to_args(start, end);
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	if (!fill_command_data(cmd, start, end))
	{
		free(cmd);
		return NULL;
	}
	return cmd;
}

/* Free command list */
static void free_command_list(t_cmd *head)
{
	t_cmd *tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->token);
		free(tmp);
	}
}

static void	init_for_norm(t_cmd	**head, t_cmd **last, int *total_pipes, t_token *tokens)
{

	*head = NULL;
	*last = NULL;
	*total_pipes = count_pipes(tokens);
}

/* Main function: split tokens and build command list */
t_cmd *ft_parse_commands(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*last;
	t_token	*start;
	t_token	*end;
	t_cmd	*cmd;
	int		total_pipes;

	init_for_norm(&head, &last, &total_pipes, tokens);
	start = tokens;
	while (start)
	{
		end = start;
		while (end && end->type != PIPE)
			end = end->next;
		cmd = parse_command_node(start, end);
		if (!cmd)
			return (free_command_list(head), NULL);
		cmd->pipe_count = total_pipes;
		if (!head)
			head = cmd;
		else
			last->next = cmd;
		last = cmd;
		start = get_next_command_tokens(end);
	}
	return (head);
}



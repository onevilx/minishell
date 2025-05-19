/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:34:57 by obouftou          #+#    #+#             */
/*   Updated: 2025/05/19 20:21:06 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

int	is_operator_start(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_meta(char c)
{
	return (c == ' ' || c == '\t'
		|| c == '|' || c == '<' || c == '>'
		|| c == '\'' || c == '"');
}

t_token	*tokenizing(const char *input)
{
	int		i;
	t_token	*tokens;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		if (ft_isspace(input[i]))
		{
			i++;
			continue ;
		}
		if (is_operator_start(input[i]))
		{
			add_token(&tokens, parse_operator(input, &i));
			continue ;
		}
		add_token(&tokens, parse_word(input, &i));
	}
	return (tokens);
}

void	ft_print_tokens(t_token *tokens)
{
	t_token	*cur;

	printf("🔎 Token list:\n");
	cur = tokens;
	while (cur)
	{
		const char *type_str = (
			cur->type == WORD ? "WORD" :
			cur->type == PIPE ? "PIPE" :
			cur->type == REDIR_IN ? "REDIR_IN" :
			cur->type == REDIR_OUT ? "REDIR_OUT" :
			cur->type == APPEND ? "APPEND" :
			cur->type == HEREDOC ? "HEREDOC" : "UNKNOWN");

		const char *quote_str = (
			cur->quote_type == '\'' ? "SINGLE" :
			cur->quote_type == '"' ? "DOUBLE" : "NONE");

		printf("  Type: %-10s | Quote: %-6s | Value: \"%s\"\n",
			type_str, quote_str, cur->value);

		// If it's a redirection operator, try to print its target
		if ((cur->type == REDIR_IN || cur->type == REDIR_OUT ||
			 cur->type == APPEND || cur->type == HEREDOC)
			&& cur->next && cur->next->type == WORD)
		{
			printf("    ↪ Redirects to: \"%s\"\n", cur->next->value);
		}
		cur = cur->next;
	}
}

static const char *redir_type_str(t_code type)
{
	if (type == REDIR_IN) return "<";
	if (type == REDIR_OUT) return ">";
	if (type == APPEND) return ">>";
	if (type == HEREDOC) return "<<";
	return "UNKNOWN";
}

void	ft_print_cmd(t_cmd *cmd)
{
	int i;
	t_redirect *redir;
	int cmd_index;

	cmd_index = 0;
	while (cmd)
	{
		printf("🔹 Command %d:\n", cmd_index++);

		// Print tokens
		printf("  🧾 Tokens:\n");
		if (cmd->token)
		{
			i = 0;
			while (cmd->token[i])
			{
				printf("    - [%d] \"%s\"\n", i, cmd->token[i]->value);
				i++;
			}
		}
		else
			printf("    (no tokens)\n");

		// Print redirections
		printf("  🔁 Redirections:\n");
		redir = cmd->red;
		if (!redir)
			printf("    (no redirections)\n");
		while (redir)
		{
			printf("    - Type: %-3s | Target: \"%s\"\n",
				redir_type_str(redir->type), redir->val);
			redir = redir->next;
		}

		// Pipe count
		printf("  🔗 Pipe count after this command: %d\n", cmd->pipe_count);

		// Next command
		cmd = cmd->next;
		if (cmd)
			printf("  ↓\n");
	}
}

t_cmd	*ft_input_proces(char *input, char **envp)
{
	t_token	*tokens;
	t_cmd	*cmd;
	// t_env	*env;

	(void)	envp;
	if (!are_quotes_closed(input))
	{
		printf("Syntax error: unclosed quote\n");
		return (NULL);
	}
	tokens = tokenizing(input);
	if (!tokens)
		return(NULL);
	ft_print_tokens(tokens);
	if(!syntax_check(tokens))
	{
		free_tokens(tokens);
		return (NULL);
	}
	// env = ft_init_env_list(envp);
	// ft_expand_tokens(tokens, env); // to do
	cmd = ft_parse_commands(tokens);
	ft_print_cmd(cmd);
	return(cmd);
}

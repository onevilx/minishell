/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onevil_x <onevil_x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:34:57 by obouftou          #+#    #+#             */
/*   Updated: 2025/05/31 20:37:02 by onevil_x         ###   ########.fr       */
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

t_token	*parse_quoted_word(const char *input, int *i)
{
	char	quote;
	char	buffer[1024];
	int		buf_i;

	buf_i = 0;
	quote = input[(*i)++];
	while (input[*i] && input[*i] != quote && buf_i < 1023)
		buffer[buf_i++] = input[(*i)++];
	if (input[*i] == quote)
		(*i)++;
	buffer[buf_i] = '\0';
	return (new_token(WORD, strdup(buffer), quote));
}


t_token	*tokenizing(const char *input)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		if (ft_isspace(input[i]))
			i++;
		else if (is_operator_start(input[i]))
			add_token(&tokens, parse_operator(input, &i));
		else if (input[i] == '$' && input[i + 1] == '"')
		{
			add_token(&tokens, new_token(WORD, strdup("$"), '"'));
			i++;
			add_token(&tokens, parse_quoted_word(input, &i));
		}
		else if (input[i] == '"' || input[i] == '\'')
			add_token(&tokens, parse_quoted_word(input, &i));
		else
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

t_cmd	*ft_input_proces(char *input, char **envp, int exit_status)
{
	t_token	*tokens;
	t_cmd	*cmd;
	t_env	*env;

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
	env = ft_init_env_list(envp);
	ft_expand_tokens(tokens, env, exit_status); // to do
	cmd = ft_parse_commands(tokens);
	ft_print_cmd(cmd);
	return(cmd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouftou <obouftou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:34:57 by obouftou          #+#    #+#             */
/*   Updated: 2025/06/21 17:59:20 by obouftou         ###   ########.fr       */
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


static void	skip_spaces(const char *input, int *i)
{
	while (input[*i] && ft_isspace(input[*i]))
		(*i)++;
}

static bool	has_space_after(const char *input, int i)
{
	while (input[i])
	{
		if (ft_isspace(input[i]))
			return (true);
		if (!ft_isspace(input[i]))
			break ;
		i++;
	}
	return (false);
}

static t_token	*parse_dollar_quote_case(const char *input, int *i, t_token **tokens)
{
	t_token	*new;

	new = new_token(WORD, strdup("$"), '"');
	add_token(tokens, new);
	(*i)++;
	return (parse_quoted_word(input, i));
}
static t_token	*parse_non_empty_word(const char *input, int *i)
{
	t_token	*new;
	
	new = parse_word(input, i);
	if (new && new->value && new->value[0] == '\0')
	{
		free(new->value);
		free(new);
		return (NULL);
	}
	return (new);
}
static t_token	*parse_and_classify(const char *input, int *i, t_token **tokens)
{
	t_token	*new;

	new = NULL;
	if (is_operator_start(input[*i]))
	new = parse_operator(input, i);
	else if (input[*i] == '$' && input[*i + 1] == '"')
	new = parse_dollar_quote_case(input, i, tokens);
	else if (input[*i] == '"' || input[*i] == '\'')
	new = parse_quoted_word(input, i);
	else
	new = parse_non_empty_word(input, i);
	return (new);
}

t_token	*tokenizing(const char *input)
{
	t_token	*tokens;
	t_token	*new;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		skip_spaces(input, &i);
		new = parse_and_classify(input, &i, &tokens);
		if (new)
		{
			new->space_after = has_space_after(input, i);
			add_token(&tokens, new);
		}
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


void	merge_tokens(t_token *head)
{
	t_token	*cur;
	t_token	*next;
	char	*joined;

	cur = head;
	while (cur && cur->next)
	{
		next = cur->next;
		if (cur->type == WORD && next->type == WORD
			&& !cur->space_after && (cur->quote_type == '\'' || cur->quote_type == '"') )
		{
			joined = ft_strjoin(cur->value, next->value);
			free(cur->value);
			cur->value = joined;

			cur->space_after = next->space_after;
			cur->next = next->next;
			free(next->value);
			free(next);
			continue;
		}
		cur = cur->next;
	}
}
void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}
t_cmd	*ft_input_proces(char *input, char **envp, int *exit_status)
{
	t_token	*tokens;
	t_cmd	*cmd;
	t_env	*env;

	(void)	envp;
	if (!are_quotes_closed(input))
	{
		printf("Syntax error: unclosed quote\n");
		*exit_status = 100;
		return (NULL);
	}
	tokens = tokenizing(input);
	if (!tokens)
		return(NULL);
	if(!syntax_check(tokens, exit_status))
	{
		free_tokens(tokens);
		return (NULL);
	}
	env = ft_init_env_list(envp);
	ft_expand_tokens(tokens, env, *exit_status);
	merge_tokens(tokens);
	ft_remove_empty(&tokens);
	cmd = ft_parse_commands(tokens);
	// free_env_list(env);
	// ft_print_cmd(cmd);
	// ft_print_tokens(tokens);
	return(cmd);
}

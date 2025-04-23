/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouftou <obouftou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:03:35 by obouftou          #+#    #+#             */
/*   Updated: 2025/04/22 20:52:12 by obouftou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/miniheader.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

bool	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

t_token	*new_token(t_code type, char *val)
{
	t_token	*tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->type = type,
	tok->value = val;
	tok->next = NULL;
	return (tok);
}
void add_token(t_token **head, t_token *new)
{
	t_token *tmp;

	if (!*head)
	{
		*head = new;
		return;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_token *parse_operator(const char *input, int *i)
{
	t_token *tok;

	if (input[*i] == '>' && input[*i + 1] == '>')
	{
		*i += 2;
		return new_token(APPEND, strdup(">>"));
	}
	if (input[*i] == '<' && input[*i + 1] == '<')
	{
		*i += 2;
		return new_token(HEREDOC, strdup("<<"));
	}
	if (input[*i] == '>')
		return new_token(REDIR_OUT, strndup(&input[(*i)++], 1));
	if (input[*i] == '<')
		return new_token(REDIR_IN, strndup(&input[(*i)++], 1));
	if (input[*i] == '|')
		return new_token(PIPE, strndup(&input[(*i)++], 1));
	return NULL;
}

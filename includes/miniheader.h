/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniheader.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouftou <obouftou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:34:48 by yaboukir          #+#    #+#             */
/*   Updated: 2025/06/20 17:53:32 by obouftou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIHEADER_H
# define MINIHEADER_H

#include <stdbool.h>

typedef enum s_code
{
	PIPE,
	HEREDOC,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	WORD,
}			t_code;

typedef struct s_gc
{
	void			*ptr;
	struct s_gc		*next;
}	t_gc;

typedef struct s_redirect
{
	t_code				type;
	char				*val;
	char				quote_type;
	struct s_redirect	*next;
}				t_redirect;

typedef struct s_token
{
	t_code			type;
	char			quote_type;
	char			*value;
	bool			space_after;
	struct s_token	*next;
}				t_token;

typedef struct s_arg
{
	char			*value;
	char			quote_type;
	struct s_arg	*next;
}				t_arg;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}			t_env;

typedef struct s_cmd
{
	int				pipe_count;
	t_arg			*args;
	t_redirect		*red;
	t_token			**token;
	struct s_cmd	*next;

}				t_cmd;

#endif

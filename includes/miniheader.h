/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniheader.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:34:48 by yaboukir          #+#    #+#             */
/*   Updated: 2025/04/23 16:39:28 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  MINIHEADER_H
# define MINIHEADER_H

typedef enum	s_code
{
	PIPE,
	HEREDOC,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	WORD,
}	t_code;

typedef struct	s_redirect
{
	t_code				type;
	char				*val;
	struct t_redirect	*next;
}		t_redirect;

typedef struct	s_token
{
	t_code			type;
	char			*value;
	struct s_token	*next;
}		t_token;

typedef struct s_cmd
{
	int		pipe_count;
	t_redirect	*red;
	t_token		**token;
	struct s_cmd	*next;

}		t_cmd;


typedef struct s_builtin
{
	char	*name;
	void	(*func)(char **args);
}				t_builtin;

#endif

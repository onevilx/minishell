/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:29:31 by yaboukir          #+#    #+#             */
/*   Updated: 2025/04/23 14:46:03 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../includes/miniheader.h"

typedef struct s_builtin
{
	char	*name;
	void	(*func)(char **args);
}				t_builtin;

typedef enum s_code
{
	PIPE,
	HEREDOC,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	WORD,
}				t_code;

typedef struct s_token
{
	char	*value;
	t_code	type;
}				t_token;

typedef struct s_cmd
{
	t_token	**tokens;
	int		pipe_count;
}				t_cmd;

int		execute_builtin(char **args);
void	builtin_cd(char **args);
void	builtin_pwd(char **args);
void	builtin_env(char **args);
void	builtin_exit(char **args);
void	builtin_echo(char **args);
void	builtin_unset(char **args);
void	builtin_export(char **args);

#endif

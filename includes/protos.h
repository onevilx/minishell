/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:05:33 by yaboukir          #+#    #+#             */
/*   Updated: 2025/04/25 01:29:09 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOS_H
# define PROTOS_H

# include "miniheader.h"
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <string.h>
# include <termios.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>

int		ft_strcmp(const char *s1, const char *s2);
int		find_env_index(char **env, char *key);
int		execute_builtin(char **args);
bool	ft_isspace(char c);
t_cmd	*ft_input_proces(char *input);
t_token	*new_token(t_code type, char *val);
t_token *parse_operator(const char *input, int *i);
char	*strndup(const char *s, size_t n);
char	*get_env_value(char *key);
int		ft_atoi(const char *str);
int		open_tmpfile(void);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	***get_env(void);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	init_signals(void);
void	init_terminal(void);
void	disable_echoctl(void);
void	sigterm_handler(int signum);
void	sigquit_handler(int signum);
void	sigint_handler(int signum);
void	init_env(char **envp);
void	write_line(int fd, char *line);
void	update_env_var(int idx, char *arg);
void	read_input(int fd, char *delimiter);
void	add_token(t_token **head, t_token *new);
void	ft_print_tokens(t_token *tokens);
void	*ft_calloc(size_t count, size_t size);
void	builtin_cd(char **args);
void	builtin_pwd(char **args);
void	builtin_env(char **args);
void	builtin_exit(char **args);
void	builtin_echo(char **args);
void	builtin_unset(char **args);
void	handle_append(t_token **tokens);
void	handle_heredoc(t_token **tokens);
void	handle_redirections(t_token **tokens);
void	builtin_export(char **args);
size_t	ft_strlen(const char *s);


#endif

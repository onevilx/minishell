/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouftou <obouftou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:05:33 by yaboukir          #+#    #+#             */
/*   Updated: 2025/05/05 20:41:22 by obouftou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOS_H
# define PROTOS_H

# include "miniheader.h"
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
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
int		execute_external(char **args);
bool	ft_isspace(char c);
t_cmd	*ft_input_proces(char *input);
t_token	*new_token(t_code type, char *val, char qoute_type);
t_token	*parse_operator(const char *input, int *i);
char	*ft_itoa(int n);
char	**copy_env(char **envp);
void	update_shlvl(void);
char	*strndup(const char *s, size_t n);
char	*get_env_value(char *key);
void	print_welcome(void);
void	free_split(char **array);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_free(char *s1, const char *s2);
int		ft_atoi(const char *str);
int		open_tmpfile(void);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	***get_env(void);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	init_signals(void);
void	ft_launching(void);
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
void	update_or_add_env(const char *key, const char *full_var);
size_t	ft_strlen(const char *s);
void	free_tokens(t_token *token);
bool 	are_quotes_closed(const char *input);
bool	syntax_check(t_token *token);
t_token	*parse_word(const char *input, int *i);
int		is_operator_start(char c);

#endif

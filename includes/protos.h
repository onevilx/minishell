/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onevil_x <onevil_x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:05:33 by yaboukir          #+#    #+#             */
/*   Updated: 2025/05/18 05:35:16 by onevil_x         ###   ########.fr       */
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
# include <stdint.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>

char		**ft_split_once(const char *s, char c);
int			ft_strcmp(const char *s1, const char *s2);
int			find_env_index(char **env, char *key);
int			parse_commands_loop(t_token *tokens, t_cmd **head,
				t_cmd **last, int total_pipes);
int			handle_redirection(t_cmd *cmd, t_token **cur,
				t_token **args, int *i);
void		init_for_norm(t_cmd	**head, t_cmd **last,
				int *total_pipes, t_token *tokens);
int			execute_builtin(t_cmd *cmd);
int			execute_external(t_cmd *cmd);
bool		ft_isspace(char c);
t_cmd		*ft_input_proces(char *input);
int			is_valid_n_flag(char *str);
t_token		*new_token(t_code type, char *val, char qoute_type);
t_token		*parse_operator(const char *input, int *i);
char		*ft_itoa(int n);
char		**copy_env(char **envp);
int			write_heredoc_tmp(char *content);
t_arg		*check_n_flag(t_arg *args, int *no_newline);
int			read_heredoc_tmp(void);
void		update_shlvl(void);
char		*strndup(const char *s, size_t n);
char		*get_env_value(char *key);
void		print_welcome(void);
void		free_split(char **array);
t_arg		*token_to_args(t_token *start, t_token *end);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strjoin_free(char *s1, const char *s2);
int			ft_atoi(const char *str);
int			open_tmpfile(void);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		***get_env(void);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strdup(const char *s1);
char		**ft_split(char const *s, char c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
void		init_signals(void);
void		ft_launching(void);
void		init_terminal(void);
void		disable_echoctl(void);
void		sigterm_handler(int signum);
void		sigquit_handler(int signum);
void		sigint_handler(int signum);
void		init_env(char **envp);
void		write_line(int fd, char *line);
void		update_env_var(int idx, char *arg);
char		*read_input(const char *delimiter);
void		handling_cmdops(t_cmd *cmd);
char		*ft_strchr(const char *s, int c);
void		free_command_list(t_cmd *head);
void		handle_child_process(t_cmd *cmd, int prev_fd, int *pipe_fd);
void		handle_parent_process(t_cmd *cmd, int *prev_fd, int pipe_fd[2]);
char		*find_command_path(char *cmd, char **env);
void		add_token(t_token **head, t_token *new);
int			is_redirection(t_token *tok);
void		ft_print_tokens(t_token *tokens);
void		save_word(t_token *cur, t_token **args, int *i);
void		*ft_calloc(size_t count, size_t size);
void		builtin_cd(t_arg *args);
void		builtin_echo(t_arg *args);
void		builtin_pwd(t_arg *args);
void		sanitize_args(t_cmd *cmd);
void		free_redirections(t_redirect *redir);
void		builtin_env(t_arg *args);
void		builtin_exit(t_arg *args);
t_token		*get_next_command_tokens(t_token *cur);
t_cmd		*parse_command_node(t_token *start, t_token *end);
int			do_append_fd(char *filename);
int			do_append_redirection(t_token *curr);
t_arg		*char_array_to_args_list(char **array);
int			execute_command(t_cmd *cmd);
void		builtin_unset(t_arg *args);
void		remove_heredoc_tokens(t_cmd *cmd);
void		handle_append(t_cmd *cmd);
void		sanitize_args(t_cmd *cmd);
void		handle_pipe(t_cmd *cmd);
void		handle_heredoc(t_cmd *cmd);
char		**convert_args(t_arg *args);
void		free_cmd(t_cmd *cmd);
void		handle_redirections(t_cmd *cmd);
void		ft_free_split(char **arr);
void		builtin_export(t_arg *args);
void		update_or_add_env(const char *key, const char *full_var);
size_t		ft_strlen(const char *s);
void		free_tokens(t_token *token);
void		free_tokensexe(t_token **tokens);
bool		are_quotes_closed(const char *input);
bool		syntax_check(t_token *token);
t_token		*parse_word(const char *input, int *i);
int			is_operator_start(char c);
t_redirect	*add_redirect(t_redirect *head, t_code type, char *val);
t_cmd		*ft_parse_commands(t_token *tokens);
int			count_pipes(t_token *tokens);

#endif

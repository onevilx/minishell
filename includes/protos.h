/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:05:33 by yaboukir          #+#    #+#             */
/*   Updated: 2025/06/30 23:02:15 by yaboukir         ###   ########.fr       */
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
# include <errno.h>
# include <stdint.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>

void		handle_ambiguous(t_token *cur, t_token *target, int *exit_status);
void		print_ambiguous_error(const char *val);
bool		is_ambiguous_target(t_token *target);
void		normalize_odd_dollars(t_token *tokens);
void		expand_token(t_token *tok, t_env *env, int status);
void		handle_export_assignment(t_token *prev, t_token **cur,
				t_env *env, int status);
void		handle_tilde_and_skip(t_token **cur, t_token *prev, t_token *next);
void		handle_regular_expansion(t_token *cur,
				t_env *env, int status);
bool		is_unquoted_export_assignment(t_token *prev, t_token *cur);
bool		has_space_after(const char *input, int i);
void		skip_spaces(const char *input, int *i);
t_token		*parse_quoted_word(const char *input, int *i);
void		pipe_loop(t_cmd *cmd);
int			copy_token_part(char *dst, int buf_i, const char *src);
char		*collect_quoted_content(const char *input, int *i,
				char *quote_type);
char		*handle_dollar(char *input, int *i, t_env *env, int status);
int			handle_quoted_part(const char *input, int *i, t_parse_ctx *ctx);
int			is_directory(const char *path);
char		*append_line(char *buffer, char *line);
char		*get_env_val_list(t_env *env, const char *key);
char		*normalize_whitespace(char *str);
void		handle_normalized_expansion(t_token *tok, char *expanded);
t_token		*split_expanded_token(char *expanded);
void		replace_token_with_multiple(t_token *old, t_token *new_tokens);
char		*extract_plain(char *input, int *i);
bool		is_localized_string(t_token *prev);
bool		handle_too_many_heredocs(t_token *cur, int *exit_status);
bool		handle_redirection(t_token *cur, int *exit_status,
				int *heredoc_idx);
char		*handle_read_loop(char *delimiter, t_env *env,
				char quote_type, int exit_status);
char		*handle_ctrl_c(char *buffer);
t_mode		*get_shell_mode(void);
bool		check_ambg(t_token *tokens, int *exit_status);
void		ft_remove_empty(t_token **tokens);
void		ft_bzero(void *s, size_t n);
int			ft_isalpha(int x);
void		*g_malloc(size_t size);
int			ft_isalnum(int x);
void		ft_expand_tokens(t_token *tokens, t_env *env, int exit_status);
t_env		*ft_init_env_list(char **env);
char		**ft_split_once(const char *s, char c);
int			ft_strcmp(const char *s1, const char *s2);
int			find_env_index(char **env, char *key);
int			is_digit_str(const char *str, int i, int sign);
int			parse_commands_loop(t_token *tokens, t_cmd **head,
				t_cmd **last, int total_pipes);
int			handle_redirection1(t_cmd *cmd, t_token **cur,
				t_token **args, int *i);
void		init_for_norm(t_cmd	**head, t_cmd **last,
				int *total_pipes, t_token *tokens);
int			execute_builtin(t_cmd *cmd);
char		*find_in_paths(char **paths, char *cmd);
void		exec_direct_path(t_cmd *cmd, char **args_array);
bool		ft_isspace(char c);
t_cmd		*ft_input_proces(char *input, char **envp, int *exit_status);
t_token		*new_token(t_code type, char *val, char qoute_type);
t_token		*parse_operator(const char *input, int *i);
char		*ft_itoa(int n);
char		**copy_env(char **envp);
int			write_heredoc_tmp(char *filename, char *content);
t_arg		*check_n_flag(t_arg *args, int *no_newline);
void		update_shlvl(void);
char		*ft_strndup(const char *s, size_t n);
char		*get_env_value(char *key);
void		try_exec_paths(t_cmd *cmd);
char		**args_to_array(t_arg *args);
void		free_split(char **array);
char		*process_line(const char *line, t_env *env,
				char quote_type, int exit_status);
t_arg		*token_to_args(t_token *start, t_token *end);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strjoin_free(char *s1, const char *s2);
int			ft_atoi(const char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		***get_env(void);
int			count_heredoc(t_token *tokens);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strdup(const char *s1);
char		**ft_split(char const *s, char c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
void		ft_launching(void);
void		init_terminal(void);
void		disable_echoctl(void);
void		sigterm_handler(int signum);
void		sigint_handler(int signum);
void		heredoc_sig(int signal);
void		print_env_vars(char **env);
int			str_in_array(char **arr, char *str);
int			builtin_exit(t_arg *args, int print_exit);
int			sanitize_all_args(t_cmd *cmd);
char		**extract_args(t_token *tok);
void		print_export_only_vars(char **export);
char		*ft_strjoin3(char *s1, char *s2, char *s3);
void		add_to_array(char ***arr_ptr, char *str);
int			is_valid_export(char *arg);
int			is_append_mode(char *value, int *pos);
void		append_to_env(char *key, char *value, int idx);
void		handle_export_logic(t_arg *arg, char *key, int append, int pos);
void		init_env(char **envp);
void		add_env_var(char *arg);
void		update_env_var(int idx, char *arg);
char		*generate_tmp_filename(int index);
char		*read_input(const char *delimiter, t_env *env,
				char quote_type, int exit_status);
int			handling_cmdops(t_cmd *cmd);
void		update_pwd_vars(char *oldpwd);
void		free_env(char **env);
t_token		*tokenizing(const char *input);
void		merge_tokens(t_token *head);
char		*ft_strchr(const char *s, int c);
char		*ft_expand_value(char *input, t_env *env, int status);
void		free_command_list(t_cmd *head);
void		handle_child_process(t_cmd *cmd, int prev_fd, int *pipe_fd);
void		handle_parent_process(t_cmd *cmd, int *prev_fd, int pipe_fd[2]);
char		*find_command_path(char *cmd, char **env);
void		add_token(t_token **head, t_token *new);
int			is_redirection(t_token *tok);
void		save_word(t_token *cur, t_token **args, int *i);
void		*ft_calloc(size_t count, size_t size);
int			builtin_cd(t_arg *args);
int			is_builtin(t_cmd *cmd);
int			*get_exit_status(void);
int			builtin_echo(t_arg *args);
int			builtin_pwd(t_arg *args);
int			sanitize_args(t_cmd *cmd);
int			builtin_env(t_arg *args);
t_token		*get_next_command_tokens(t_token *cur);
t_cmd		*parse_command_node(t_token *start, t_token *end);
int			do_append_redirection(t_redirect *curr);
int			execute_command(t_cmd *cmd);
int			builtin_unset(t_arg *args);
void		cleanup_cmdops_files(t_cmd *cmd);
int			handle_append(t_cmd *cmd);
void		reset_init_signals(void);
void		reset_signal(void);
void		ignore_signal(void);
void		handle_pipe(t_cmd *cmd);
char		**convert_args(t_arg *args);
int			handle_redirections(t_cmd *cmd);
void		*ft_free(char **arr, int count);
void		ft_free_split(char **arr);
size_t		get_len(char const *s, char c);
int			builtin_export(t_arg *args);
void		update_or_add_env(const char *key, const char *full_var);
size_t		ft_strlen(const char *s);
int			handle_redir_in(t_redirect *redir);
int			handle_redir_out(t_redirect *redir);
char		*join_token_values(t_token *tokens);
bool		are_quotes_closed(const char *input);
bool		syntax_check(t_token *token, int *exit_status);
t_token		*parse_word(const char *input, int *i);
void		wait_for_children(pid_t last_pid);
int			create_pipe(int pipe_fd[2]);
char		**get_paths_array(void);
void		try_exec_in_paths(char **paths, char **args_array, char **env);
pid_t		do_fork(pid_t last_pid, int pipe_fd[2], int prev_fd);
int			is_operator_start(char c);
t_redirect	*add_redirect(t_redirect *head, t_code type, char *val);
t_cmd		*ft_parse_commands(t_token *tokens);

#endif

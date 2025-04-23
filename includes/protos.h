/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:05:33 by yaboukir          #+#    #+#             */
/*   Updated: 2025/04/23 15:36:40 by yaboukir         ###   ########.fr       */
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
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdbool.h>

t_cmd	*ft_input_proces(char *input);
int		ft_strcmp(const char *s1, const char *s2);
bool	ft_isspace(char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
t_token	*new_token(t_code type, char *val);
void	add_token(t_token **head, t_token *new);
char	*strndup(const char *s, size_t n);
t_token *parse_operator(const char *input, int *i);
int		ft_atoi(const char *str);
int		open_tmpfile(void);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	***get_env(void);
char	*ft_strdup(const char *s1);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	init_env(char **envp);
void	write_line(int fd, char *line);
void	read_input(int fd, char *delimiter);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *s);


#endif


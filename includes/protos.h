#ifndef PROTOS_H
# define PROTOS_H

t_cmd	*ft_input_proces(char *input);
int		ft_strcmp(const char *s1, const char *s2);
bool	ft_isspace(char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
t_token	*new_token(t_code type, char *val);
void	add_token(t_token **head, t_token *new);
char	*strndup(const char *s, size_t n);
t_token *parse_operator(const char *input, int *i);



#endif


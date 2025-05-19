


//so know i got an idea of storing the 2d array into an linked list so i can easly backtrace what i need and traverse it freely ]
// so i will get the envp into linked list by soting every env[1] into t_env value/ key
// so ill creat a function that split every string of the env pointer to two part befor '=' and assinge it to the key and the after '=' and assigne it to the value;
// costume split in the way same concept but the delimiter will be the = ;
//and so on till i get all the envirement stored in my linnked list;;

// #include "../includes/protos.h"




// char	*expand_value(char *value, t_env *env)
// {




// }


// void	ft_expand_tokens(t_token *tokens, t_env *env)
// {
// 	char	*expanded;
// 	//how i could do this ??
// 	while (tokens)
// 	{
// 		if (tokens->quote_type == '\'')
// 			tokens = tokens->next;
// 		else if (ft_s trchr(tokens->value, '$')
// 			&& (tokens->quote_type == '\0' || tokens->quote_type == '"'))
// 			{
// 				expanded = expand_value(tokens->value, env);
// 			}
// 		tokens = tokens->next;
// 	}
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:43:23 by yaboukir          #+#    #+#             */
/*   Updated: 2025/05/14 16:32:21 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

// Helper function to convert linked list of t_arg to char ** (array of strings)
static char **args_to_array(t_arg *args)
{
    t_arg  *current;
    int     count;
    char    **arr;
    int     i;

    // Count the number of arguments in the linked list
    count = 0;
    current = args;
    while (current)
    {
        count++;
        current = current->next;
    }

    // Allocate memory for the array of strings
    arr = malloc(sizeof(char *) * (count + 1));  // +1 for NULL terminator
    if (!arr)
        return (NULL);

    // Fill the array with values from the linked list
    current = args;
    i = 0;
    while (current)
    {
        arr[i] = ft_strdup(current->value);  // Copy string from t_arg
        current = current->next;
        i++;
    }
    arr[i] = NULL;  // Null-terminate the array

    return (arr);
}

// Try executing the command using paths in $PATH
static void try_exec_paths(t_cmd *cmd)
{
    char    **paths;
    char    *path;
    int     i;
    char    **args_array;

    paths = ft_split(getenv("PATH"), ':');
    if (!paths)
        exit(1);

    // Convert linked list args to array for execve
    args_array = args_to_array(cmd->args);
    if (!args_array)
        exit(1);

    i = 0;
    while (paths[i])
    {
        path = ft_strjoin(paths[i], "/");
        path = ft_strjoin_free(path, args_array[0]);
        if (access(path, X_OK) == 0)
            execve(path, args_array, *get_env());
        free(path);
        i++;
    }
    free_split(paths);
    free(args_array);  // Free the allocated array

    printf("minishell: command not found: %s\n", args_array[0]);
    exit(127);
}

// Execute external commands
int execute_external(t_cmd *cmd)
{
    pid_t   pid;
    int     status;

    if (!cmd->args || !cmd->args->value)
        return (0);

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return (0);
    }
    else if (pid == 0)
    {
        // Convert linked list args to array for execve
        char **args_array = args_to_array(cmd->args);
        if (!args_array)
            exit(1);

        if (access(cmd->args->value, X_OK) == 0)
            execve(cmd->args->value, args_array, *get_env());
        try_exec_paths(cmd);
        free(args_array);  // Free the allocated array
    }
    else
        waitpid(pid, &status, 0);

    return (1);
}

t_arg *token_to_args(t_token *start, t_token *end)
{
	t_arg *head = NULL;
	t_arg *tail = NULL;

	while (start && start != end)
	{
		if (start->type == WORD)
		{
			t_arg *new_arg = malloc(sizeof(t_arg));
			if (!new_arg)
				return (NULL); // Optionally free previous args on error
			new_arg->value = ft_strdup(start->value);
			new_arg->next = NULL;

			if (!head)
				head = new_arg;
			else
				tail->next = new_arg;
			tail = new_arg;
		}
		start = start->next;
	}
	return head;
}


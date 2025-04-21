/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:31:11 by yaboukir          #+#    #+#             */
/*   Updated: 2025/04/21 18:22:43 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_welcome(void)
{
    printf("🟢 Welcome to \033[1;32mminishell\033[0m, this project built by pinky and the brain!\n");
}

int main (void)
{
	char *input;

	print_welcome();
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit!\n");
			break ;
		}
		if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		//hna action ghayw93 bchwya 3lina !!
		free(input);
	}
	return (0);
}

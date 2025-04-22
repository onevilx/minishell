/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouftou <obouftou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:30:28 by obouftou          #+#    #+#             */
/*   Updated: 2025/04/22 15:31:25 by obouftou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/miniheader.h"


void print_welcome(void)
{
    printf("🟢 Welcome to \033[1;32mminishell\033[0m, this project built by pinky and the brain!\n");
}

int main (void)
{
	char	*input;
	char	*cmd;

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
		cmd = ft_input_process(input);
		//hna action ghayw93 bchwya 3lina !!
		free(input);
	}
	return (0);
}

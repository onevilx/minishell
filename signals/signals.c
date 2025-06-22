/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboukir <yaboukir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:45:18 by obouftou          #+#    #+#             */
/*   Updated: 2025/06/22 00:41:42 by yaboukir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/protos.h"

void	sigint_handler(int signum)
{
	(void)signum;
	rl_catch_signals = 0;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	*get_exit_status() = 130;
}

void	sigquit_handler(int signum)
{
	(void)signum;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigterm_handler(int signum)
{
	char	*prompt;

	(void)signum;
	prompt = "minishell$ ";
	write(1, "\033[1A", 4);
	write(1, "\033[2K", 4);
	write(1, prompt, ft_strlen(prompt));
	write(1, "exit\n", 5);
	exit (*get_exit_status());
}

void	init_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	signal(SIGTERM, sigterm_handler);
}

void	init_terminal(void)
{
	init_signals();
	disable_echoctl();
}

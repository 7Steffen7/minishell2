/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 00:17:26 by sparth            #+#    #+#             */
/*   Updated: 2024/04/16 00:18:09 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	sig_action(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
		return ;
}

void	pre_rl_signals(void)
{
		rl_catch_signals = 0;
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sig_action);
}

void	sig_child_int(int sig)
{
	(void)sig;
	exit(1);
}

void	sig_child_quit(int sig)
{
	(void)sig;
	exit(1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 17:23:01 by mhassani          #+#    #+#             */
/*   Updated: 2023/07/19 17:33:59 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_signal(int sigint)
{
	(void)sigint;
	write(1, "^C\n", 3);
}

void	ctrl_c(int sigint)
{
	write(1, "\n", 1);
	(void)sigint;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_g.exit_status = 1;
}

void	sig_handler(int sigint)
{
	(void)sigint;
	write(1, "\n", 1);
}

void	ctrl_c_herdoc(int sigint)
{
	(void)sigint;
	exit(1);
}

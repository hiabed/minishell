/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 17:23:01 by mhassani          #+#    #+#             */
/*   Updated: 2023/07/07 17:24:39 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    cmd_signal(int sigint)
{
    (void)sigint;
    write(1, "\n", 1);
}

void	ctrl_c(int sigint)
{
    write(1, "\n", 1);
	(void)sigint;
    rl_on_new_line(); // Move to a new line
    rl_replace_line("", 0); // Clear the current input line
    rl_redisplay(); // Redisplay the prompt
}
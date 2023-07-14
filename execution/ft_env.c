/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 18:40:02 by mkatfi            #+#    #+#             */
/*   Updated: 2023/07/14 15:30:47 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"../minishell.h"

void ft_env(t_env *p, t_token *ptr)
{
	
	while (p)
	{
		if (p->valuer != NULL)
		{
			ft_putstr_fd(p->key, ptr->out);
			ft_putchar_fd('=', ptr->out);
			ft_putstr_fd(p->valuer, ptr->out);
			ft_putchar_fd('\n', ptr->out);
		}
		p = p->next;
	}
	g_g.exit_status = 0;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkatfi <mkatfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 18:40:02 by mkatfi            #+#    #+#             */
/*   Updated: 2023/06/25 16:15:22 by mkatfi           ###   ########.fr       */
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
}
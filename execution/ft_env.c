/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 18:40:02 by mkatfi            #+#    #+#             */
/*   Updated: 2023/06/22 20:42:20 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_env(t_env *p)
{
	while (p )
	{
		if (p->valuer)
		{
			ft_putstr_fd(p->key, 1);
			ft_putchar_fd('=', 1);
			ft_putstr_fd(p->valuer, 1);
			ft_putchar_fd('\n', 1);
		}
		p = p->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_helper2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 20:43:23 by mhassani          #+#    #+#             */
/*   Updated: 2023/07/20 20:43:36 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_errors(int out, char *file, int i)
{
	if (i == 1)
	{
		if (access(file, W_OK) == -1 && !access(file, F_OK))
			write_error_2();
		else if (out == -1)
		{
			ft_error_2(file, 5);
			return ;
		}
	}
	if (i == 2)
	{
		ft_error_2(file, 5);
		g_g.red_check = 1;
		return ;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_Error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:26:32 by mkatfi            #+#    #+#             */
/*   Updated: 2023/07/17 19:39:59 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void ft_Error(char* s, int i)
{
    if (i == 1)
    {
        write(2, "ash: export:", 13);
        write(2, s, ft_strlen(s));
        write(2, ": not a valid identifier1\n", 27);
    }
    if (i == 2)
    {
        write(2, "minishell: cd:", 16);
        write(2, s, ft_strlen(s));
        write(2, ": not set\n", 11);
    }
    if (i == 3)
    {
        ft_putstr_fd("minishell: " ,2);
        ft_putstr_fd(s ,2);
        ft_putendl_fd(": command not found",2);
    }
}
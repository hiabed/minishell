/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_Error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:26:32 by mkatfi            #+#    #+#             */
/*   Updated: 2023/07/17 23:55:03 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void ft_Error(char* s, int i)
{
    if (i == 1)
    {
        write(2, "ash: export: `", 15);
        write(2, s, ft_strlen(s));
        write(2, "': not a valid identifier\n", 27);
    }
    if (i == 2)
    {
        write(2, "minishell : cd: ", 17);
        write(2, s, ft_strlen(s));
        write(2, ": No such file or directory\n", 29);
    }
    if (i == 3)
    {
        write(2, "minishell : cd: ", 17);
        write(2, s, ft_strlen(s));
        write(2, " No set\n", 10);
    }
    if (i == 4)
    {
        write(2, "minishell: exit: ", 18);
        write(2, s, ft_strlen(s));
        write(2, " : numeric argument required", 29);
    }
    if (i == 5)
    {
        write(2, "minishell : ", 12);
        write(2, s, ft_strlen(s));
        write(2, ": No such file or directory\n", 28);
    }
}
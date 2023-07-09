/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_Error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkatfi <mkatfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:26:32 by mkatfi            #+#    #+#             */
/*   Updated: 2023/06/25 11:29:24 by mkatfi           ###   ########.fr       */
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
        write(2, "minishell : cd:", 16);
        write(2, s, ft_strlen(s));
        write(2, ": not set\n", 11);
    }
}
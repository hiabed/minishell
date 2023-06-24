/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_Error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:26:32 by mkatfi            #+#    #+#             */
/*   Updated: 2023/06/22 20:42:26 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_Error(char* s)
{
    write(2, "ash: export:", 13);
    write(2, s, ft_strlen(s));
    write(2, ": not a valid identifier1\n", 27);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_Error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:26:32 by mkatfi            #+#    #+#             */
/*   Updated: 2023/07/19 20:19:41 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(char *s, int i)
{
	if (i == 1)
	{
		write(2, "minishell: export: `", 20);
		write(2, s, ft_strlen(s));
		write(2, "': not a valid identifier\n", 26);
	}
	if (i == 2)
	{
		write(2, "minishell : cd: ", 16);
		write(2, s, ft_strlen(s));
		write(2, ": No such file or directory\n", 28);
	}
	if (i == 3)
	{
		write(2, "minishell : cd: ", 16);
		write(2, s, ft_strlen(s));
		write(2, " No set\n", 8);
	}
	if (i == 8)
    {
        write(2, "minishell : exit: ", 18);
        write(2, s, ft_strlen(s));
        write(2, " too many arguments\n", 20);
    }
}

void	ft_error_2(char *s, int i)
{
	if (i == 4)
	{
		write(2, "minishell: exit: ", 17);
		write(2, s, ft_strlen(s));
		write(2, " : numeric argument required", 28);
	}
	if (i == 5)
	{
		write(2, "minishell : ", 12);
		write(2, s, ft_strlen(s));
		write(2, ": No such file or directory\n", 28);
	}
	if (i == 6)
	{
		write(2, "minishell : ", 12);
		write(2, s, ft_strlen(s));
		write(2, ": command not found\n", 20);
	}
	if (i == 7)
	{
		write(2, "minishell : ", 12);
		write(2, s, ft_strlen(s));
		write(2, ": is a directory\n", 17);
	}
}

void    ft_error_3(char* s, int i)
{
      if (i == 1)
    {
        write(2, "minishell: unset: `", 20);
        write(2, s, ft_strlen(s));
        write(2, "': not a valid identifier\n", 26);
    }
}


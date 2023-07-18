/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:31:39 by mkatfi            #+#    #+#             */
/*   Updated: 2023/07/18 22:32:08 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

long long	fft_atoi(const char* str)
{
    long long			i;
	long long			a;
	unsigned long	nb;

	i = 0;
	a = 1;
    nb = 0;
    if (!str)
        return(0);
    while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			a *= -1;
		i++;
    }
    while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
    {
        nb = (str[i] - 48) + nb * 10;
        if ((nb > 9223372036854775807 && a > 0) || (nb > 9223372036854775807 && a < 0))
        {
            printf("minishell: exit: %s : numeric argument required\n", str);
            g_g.exit_status = 255;
            return (0);
        }
        i++;
    }
	return (nb * a);
}

int  chaeck_nb(char* s)
{
    int i;

    i = 0;
    if (!s)
    {
        return(3);
    }
    while(s[i])
    {
        if (s[i] == '-')
            i++;
        if (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
		    i++;
        else if (!ft_isdigit(s[i]))
            return(1);
        i++;
    }
    return (0);
}

void ft_exit( char** s)
{
    long long nb;

    chaeck_nb(*s);
    nb = fft_atoi(*s);
    printf("exit\n");
    if (!s[0])
        exit(g_g.exit_status);
    else if (chaeck_nb(*s) == 1)
    {
        printf("minishell: exit: %s : numeric argument required\n", *s);
        g_g.exit_status = 255;
        exit(g_g.exit_status);
    }
    else if (ft_isdigit(s[0][0]) && s[1])
    {
        g_g.exit_status = 1;
        printf("too many arguments\n");
    } 
    else if (chaeck_nb(s[0]) == 0)
        exit(nb);
}

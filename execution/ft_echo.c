/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:54:30 by mkatfi            #+#    #+#             */
/*   Updated: 2023/06/22 20:42:04 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_size_n(char *s)
{
	int i =1;
	
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
			i++;
	}
	return (1);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] == '\0')
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if ((unsigned char)s1[i] > (unsigned char)s2[i]
			|| (unsigned char)s1[i] < (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void ft_echo(char** arg, int fd)
{
	int i;
	int cont;

	cont = 0;
	i = 0;
	if (ft_strcmp(arg[0], "") == 0)
	{
		printf("\n");
		return;
	}
	while (arg[i] && !ft_strncmp(arg[i], "-n", 2) && ft_size_n(arg[i]))
	{
		cont = 1;
		i++;
	}
	while (arg[i])
	{
		ft_putstr_fd(arg[i], fd);
		if (arg[i + 1] != '\0')
			write(1, " ", 1);
		i++;
	}
	if (cont == 0)
		write(1, "\n", 1);
}
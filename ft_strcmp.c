/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkatfi <mkatfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:55:59 by mkatfi            #+#    #+#             */
/*   Updated: 2023/06/21 22:34:55 by mkatfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	ft_strcmp(char* str1, char* str2)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	i = 0;
	if (!s1 || !s2)
		return (0);
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}	
	return (0);
}
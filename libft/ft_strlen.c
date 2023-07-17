/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 20:40:42 by mhassani          #+#    #+#             */
/*   Updated: 2023/07/17 22:44:49 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if(!s || !s[0])
		return 0;
	while (s[i])
		i++;
	return (i);
}

// int main()
// {
// 	char a[] = "hello";
// 	printf("%zu", ft_strlen(a));
// 	return 0;
// }

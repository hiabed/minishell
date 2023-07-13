/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 14:15:26 by mhassani          #+#    #+#             */
/*   Updated: 2023/07/13 11:38:50 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	count;
	char	*ptr;
	size_t	i;

	count = ft_strlen(s1) + 1;
	ptr = (char *)malloc(count * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		*(ptr + i) = *(s1 + i);
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

// int	main(void)
// {
// 	printf("%s\n", ft_strdup(">hello>>wo<rld<<"));
// }

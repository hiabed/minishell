/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 18:14:51 by mhassani          #+#    #+#             */
/*   Updated: 2023/07/08 18:07:24 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	newstr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!newstr)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		newstr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		newstr[i] = s2[j];
		i++;
		j++;
	}
	newstr[i] = '\0';
	return (newstr);
}
char	*ft_strjoin_f(char *s1, char *s2)
{
	char	*newstr;
	int		i;
	int		j;
	// printf("file %s line %d, %p   ,%s\n", __FILE__, __LINE__,s1, s1);
	// printf("file %s line %d, %p   ,%s\n", __FILE__, __LINE__, s2, s2);
	newstr = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!newstr)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		newstr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		newstr[i] = s2[j];
		i++;
		j++;
	}
	free(s1);
	// free(s2);
	newstr[i] = '\0';
	return (newstr);
}

// int	main(void)
// {
// 	printf("%s", ft_strjoin("Hello ", "world"));
// 	return (0);
// }

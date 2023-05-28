/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 14:15:26 by mhassani          #+#    #+#             */
/*   Updated: 2023/05/28 23:08:25 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	cmd_lenght(const char *s)
{
	int	i;
	int	count;
	int	len;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '>' || s[i] == '<')
			count++;
		i++;
	}
	len = (count * 2) + i;
	return (len);
}

void	ft_fill_ptr(const char *s1, char *ptr, int i, int j)
{
	while (s1[i])
	{
		if ((s1[i] == '>' && s1[i + 1] == '>') || (s1[i] == '<' && s1[i
					+ 1] == '<'))
		{
			ptr[j++] = ' ';
			ptr[j++] = s1[i];
			ptr[j++] = s1[i + 1];
			ptr[j++] = ' ';
			i++;
		}
		else if (s1[i] == '>' || s1[i] == '<')
		{
			ptr[j++] = ' ';
			ptr[j++] = s1[i];
			ptr[j++] = ' ';
		}
		else
			ptr[j++] = s1[i];
		i++;
	}
	ptr[j] = '\0';
}

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	i;
	size_t	j;

	ptr = (char *)malloc(cmd_lenght(s1) + 1);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	j = 0;
	ft_fill_ptr(s1, ptr, i, j);
	return (ptr);
}

// int	main(void)
// {
// 	char	*ptr_2;

// 	ptr_2 = ft_strdup(">hello>>wo<rld<<");
// 	printf("%s\n", ptr_2);
// }

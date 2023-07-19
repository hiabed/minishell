/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:36:32 by mhassani          #+#    #+#             */
/*   Updated: 2023/07/19 16:04:51 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_newline(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	char	*p;

	if (size && count > SIZE_MAX / size)
		return (NULL);
	i = 0;
	p = malloc(count * size);
	if (!p)
		return (NULL);
	while (i < count * size)
	{
		p[i] = 0;
		i++;
	}
	return (p);
}

char	*ft_strjoin_x(char *s1, char *s2)
{
	char	*newstr;
	int		i;
	int		j;

	if (!s1)
		s1 = ft_calloc(1, 1);
	if (!s2)
		return (NULL);
	newstr = malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
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
		newstr[i++] = s2[j++];
	newstr[i] = '\0';
	free(s1);
	return (newstr);
}

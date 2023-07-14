/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:36:49 by mhassani          #+#    #+#             */
/*   Updated: 2023/07/14 21:43:29 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char *s1, char *s2)
{
	free(s1);
	free(s2);
}

char	*line(char *s)
{
	int		i;
	char	*line;

	i = 0;
	while (s[i] != '\n' && s[i])
		i++;
	if (s[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		line[i] = s[i];
		i++;
	}
	if (s[i] == '\n' && s[i])
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*left_str(char *s)
{
	int		i;
	int		j;
	char	*left_str;

	i = 0;
	while (s[i] != '\n' && s[i])
		i++;
	left_str = malloc((ft_strlen(s) - i + 1));
	if (!left_str)
		return (NULL);
	if (s[i] && !s[i + 1])
	{
		ft_free(s, left_str);
		return (NULL);
	}
	if (s[i])
		i++;
	j = 0;
	while (s[i])
		left_str[j++] = s[i++];
	left_str[j] = '\0';
	free(s);
	return (left_str);
}

char	*read_line(int fd, int i, char *s)
{
	char	*buffer;

	buffer = malloc((size_t)(BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (!ft_newline(s) && i != 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
		{
			ft_free(s, buffer);
			return (NULL);
		}
		if (i == 0 && (!s || !s[0]))
		{
			ft_free(s, buffer);
			return (NULL);
		}
		buffer[i] = '\0';
		s = ft_strjoin_x(s, buffer);
	}
	free(buffer);
	return (s);
}

char	*get_next_line(int fd)
{
	static char	*stat;
	char		*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stat = read_line(fd, 1, stat);
	if (!stat)
		return (NULL);
	str = line(stat);
	if (!str)
		return (NULL);
	stat = left_str(stat);
	return (str);
}

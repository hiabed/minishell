/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_arround_red.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 14:15:26 by mhassani          #+#    #+#             */
/*   Updated: 2023/06/21 20:34:43 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_lenght(char *s)
{
	int	i;
	int	count;
	int	len;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == 34 || s[i] == 39)
		{
			i++;
			while (s[i] && (s[i] != 34 && s[i] != 39))
				i++;
		}
		if (s[i] == '>' || s[i] == '<')
			count++;
		i++;
	}
	len = (count * 2) + i;
	return (len);
}

void	fill_inside_d_quotes(int *i, int *j, char *ptr, char *s1)
{
	ptr[(*j)++] = s1[(*i)++];
	while (s1[*i] && s1[*i] != '\"')
		ptr[(*j)++] = s1[(*i)++];
	ptr[(*j)++] = s1[*i];
}

void	fill_inside_s_quotes(int *i, int *j, char *ptr, char *s1)
{
	ptr[(*j)++] = s1[(*i)++];
	while (s1[*i] && s1[*i] != '\'')
		ptr[(*j)++] = s1[(*i)++];
	ptr[(*j)++] = s1[*i];
}

void	ft_fill_ptr(char *s1, char *ptr, int i, int j)
{
	while (s1[i])
	{
		if (s1[i] == '\"')
			fill_inside_d_quotes(&i, &j, ptr, s1);
		else if (s1[i] == '\'')
			fill_inside_s_quotes(&i, &j, ptr, s1);
		else if ((s1[i] == '>' && s1[i + 1] == '>') || (s1[i] == '<' && s1[i
					+ 1] == '<'))
		{
			ptr[j++] = ' ';
			ptr[j++] = s1[i++];
			ptr[j++] = s1[i];
			ptr[j++] = ' ';
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

char	*space_arround_red(char *s1)
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
// 	printf("%s\n", ft_strdup(">hello>>wo<rld<<"));
// }

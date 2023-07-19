/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 19:01:48 by mhassani          #+#    #+#             */
/*   Updated: 2023/07/19 17:35:56 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	number_words(char const *s)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (s[i])
	{
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		if (s[i])
		{
			while (s[i] && (s[i] != ' ' && s[i] != '\t'))
				i++;
			n++;
		}
	}
	return (n);
}

int	word_length(char const *s, int i)
{
	int	wc;

	wc = 0;
	while (s[i] && (s[i] != ' ' && s[i] != '\t'))
	{
		i++;
		wc++;
	}
	return (wc);
}

char	**fill_array(char **tab, char const *s, int i)
{
	int	j;

	j = 0;
	while (*s)
	{
		i = 0;
		if (*s != ' ' && *s != '\t')
		{
			tab[j] = (char *)malloc((word_length(s, 0) + 1) * sizeof(char));
			if (!tab[j])
				return (NULL);
			while (*s && (*s != ' ' && *s != '\t'))
			{
				tab[j][i] = *s;
				s++;
				i++;
			}
			tab[j][i] = '\0';
			j++;
		}
		else
			s++;
	}
	tab[j] = NULL;
	return (tab);
}

//wc :<<words count>>
char	**ft_split_space(char const *s)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = (char **)malloc((number_words(s) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	fill_array(tab, s, 0);
	return (tab);
}

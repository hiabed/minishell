/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_words.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:05:20 by mhassani          #+#    #+#             */
/*   Updated: 2023/06/21 16:28:01 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*empty_string(char *str, int *i)
{
	str = malloc(1);
	str[0] = '\0';
	*i = *i + 2;
	return (str);
}

char	*fill_word_without_quotes(char *str, char *words, int *i)
{
	int	j;

	j = 0;
	str = malloc(len(&words[*i]) + 1);
	while (words[*i] && words[*i] != '\"' && words[*i] != '\'')
		str[j++] = words[(*i)++];
	str[j] = '\0';
	return (str);
}

char	*fill_word_with_d_quotes(char *str, char *words, int *i)
{
	int	j;

	j = 0;
	(*i)++;
	str = malloc(word_len(&words[*i]) + 1);
	while (words[*i] && words[*i] != '\"')
		str[j++] = words[(*i)++];
	str[j] = '\0';
	if (words[*i])
		(*i)++;
	return (str);
}

char	*fill_word_with_s_quotes(char *str, char *words, int *i)
{
	int	j;

	j = 0;
	(*i)++;
	str = malloc(word_len_single(&words[*i]) + 1);
	while (words[*i] && words[*i] != '\'')
		str[j++] = words[(*i)++];
	str[j] = '\0';
	if (words[*i])
		(*i)++;
	// printf("str: %s\n", str);
	return (str);
}

char	*fill_expand(char *str, char **envp)
{
	int		i;
	int		j;
	int		size;
	char	*expand;

	if (ft_expand_value(str, envp))
	{
		i = 0;
		j = 0;
		size = (ft_strlen(ft_expand_value(str, envp)) + 1);
		expand = ft_expand_value(str, envp);
		str = malloc(size + 1);
		while (expand[j])
			str[i++] = expand[j++];
		str[i] = '\0';
	}
	return (str);
}

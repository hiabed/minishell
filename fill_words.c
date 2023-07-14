/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_words.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:05:20 by mhassani          #+#    #+#             */
/*   Updated: 2023/07/14 23:49:58 by mhassani         ###   ########.fr       */
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

char	*fill_word_without_q(char *str, char *words, int *i)
{
	int	j;

	j = 0;
	str = malloc(len(&words[*i]) + 1);
	while (words[*i] && words[*i] != '\"' && words[*i] != '\'')
		str[j++] = words[(*i)++];
	str[j] = '\0';
	return (str);
}

char	*fill_word_with_d_q(char *str, char *words, int *i)
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

char	*fill_word_with_s_q(char *str, char *words, int *i)
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
	return (str);
}

char	*fill_expand(char *str, t_env *envp)
{
	int		i;
	int		j;
	int		size;
	char *expand = NULL;
	char *exp = ft_expand_value(str, envp);

	if (exp)
	{
		i = 0;
		j = 0;
		size = ft_strlen(exp) + 1;
		expand = exp;
		free(str);
		str = NULL;
		str = malloc(size);
		while (expand[j])
			str[i++] = expand[j++];
		str[i] = '\0';
	}
	free(expand);
	return (str);
}

char	*fill_expand_without_q(char *str, t_env *envp)
{
	int		i;
	int		j;
	int		size;
	char	*expand = NULL;
	char *exp = ft_expand_value_without_q(str, envp);

	if (exp)
	{
		i = 0;
		j = 0;
		size = (ft_strlen(exp) + 1);
		expand = exp;
		free(str);
		str = NULL;
		str = malloc(size);
		while (expand[j])
			str[i++] = expand[j++];
		str[i] = '\0';
	}
	free(expand);
	return (str);
}

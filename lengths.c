/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lengths.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 20:31:36 by mhassani          #+#    #+#             */
/*   Updated: 2023/06/18 20:32:07 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_quotes(char *words, int *i, int *count)
{
	(*i)++;
	while (words[*i] && words[*i] != '\"')
		(*i)++;
	if (words[*i])
		(*i)++;
	(*count)++;
}

int	count_strings(char *words)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (words[i])
	{
		if (words[i + 1] && ((words[i] == '\"' && words[i + 1] == '\"')
				|| (words[i] == '\'' && words[i + 1] == '\'')))
		{
			i = i + 2;
			count++;
		}
		else if (words[i] == '\"' && words[i + 1] != '\"')
			skip_quotes(words, &i, &count);
		else if (words[i] == '\'' && words[i + 1] != '\'')
			skip_quotes(words, &i, &count);
		else if (words[i] != '\"' && words[i] != '\'')
		{
			while (words[i] && (words[i] != '\"' && words[i] != '\''))
				i++;
			count++;
		}
	}
	return (count);
}

int	word_len(char *words)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (words[i] && words[i] != '\"')
	{
		count++;
		i++;
	}
	return (count);
}

int	word_len_single(char *words)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (words[i] && words[i] != '\'')
	{
		count++;
		i++;
	}
	return (count);
}

int	len(char *words)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (words[i] && words[i] != '\'' && words[i] != '\"')
	{
		count++;
		i++;
	}
	return (count);
}
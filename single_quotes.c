/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:44:21 by mhassani          #+#    #+#             */
/*   Updated: 2023/06/10 15:51:32 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_strings_single(char *words)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (words[i] && words[i + 1])
	{
		if (words[i + 1] && words[i] == '\'' && words[i + 1] == '\'')
		{
			count++;
			i = i + 2;
		}
		else if (words[i + 1] && (words[i] == '\'' && words[i + 1] != '\''))
		{
			i++;
			while (words[i] && words[i] != '\'')
				i++;
			count++;
			i++;
		}
		else if (words[i] != '\"')
		{
			while (words[i] && words[i] != '\'')
				i++;
			count++;
		}
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

char	**strings_without_single_quotes(char *words)
{
	int		i;
	int		j;
	int		k;
	char	**no_quotes_str;

	no_quotes_str = malloc((count_strings_single(words) + 1) * sizeof(char *));
	k = 0;
	i = 0;
	while (words[i] && words[i + 1])
	{
		if (words[i] == '\'' && words[i + 1] == '\'')
		{
			no_quotes_str[k] = malloc(1);
			no_quotes_str[k][0] = '\0';
			k++;
			i = i + 2;
		}
		else if ((words[i] == '\'' && words[i + 1] != '\''))
		{
			j = 0;
			i++;
			no_quotes_str[k] = malloc(word_len_single(&words[i]) + 1);
			while (words[i] && words[i] != '\'')
				no_quotes_str[k][j++] = words[i++];
			no_quotes_str[k][j] = '\0';
			k++;
			i++;
		}
		else
		{
			j = 0;
			no_quotes_str[k] = malloc(word_len_single(&words[i]) + 1);
			while (words[i] && words[i] != '\'')
				no_quotes_str[k][j++] = words[i++];
			no_quotes_str[k][j] = '\0';
			k++;
		}
	}
	no_quotes_str[k] = NULL;
	return (no_quotes_str);
}

char	*join_strings_single(char *words)
{
	int		i;
	char	*joined_string;
	char	**to_be_joined;
	char	*temp;

	i = 0;
	joined_string = NULL;
	to_be_joined = strings_without_single_quotes(words);
	if (to_be_joined[i])
	{
		joined_string = to_be_joined[i];
		while (to_be_joined[i + 1])
		{
			temp = ft_strjoin(joined_string, to_be_joined[i + 1]);
			joined_string = temp;
			i++;
		}
	}
	return (joined_string);
}

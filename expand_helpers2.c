/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helpers2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 20:44:34 by mhassani          #+#    #+#             */
/*   Updated: 2023/06/20 17:57:00 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	before_dollar_len(char *no_quotes)
{
	int	i;

	i = 0;
	while (no_quotes[i] && no_quotes[i] != '$')
		i++;
	return (i);
}

int	num_dollars(char *no_quotes)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (no_quotes[i] && no_quotes[i] == '$')
	{
		count++;
		i++;
	}
	return (count);
}

int	after_expand_check(char *no_quotes)
{
	int	i;
	int	j;
	int	k;
	int	len;

	i = 0;
	k = 0;
	len = 0;
	j = 0;
	while (no_quotes[i] && no_quotes[i] != '\'' && no_quotes[i] != '+'
		&& no_quotes[i] != '.' && no_quotes[i] != '$')
	{
		k++;
		i++;
	}
	while (no_quotes[k] && no_quotes[k] != '$')
	{
		k++;
		len++;
	}
	if (!len)
		return (0);
	if (len)
		return (1);
	return (1);
}

char	*fst_chars(char *no_quotes, int i)
{
	char	*chars;
	int		j;

	j = 0;
	chars = malloc(before_dollar_len(no_quotes) + 1);
	while (no_quotes[i] && no_quotes[i] != '$')
		chars[j++] = no_quotes[(i)++];
	chars[j] = '\0';
	return (chars);
}

char	*only_dollar(char *no_q, char *temp)
{
	int		i;
	char	*status;

	i = 0;
	if (no_q[i] == '$' && !no_q[i + 1])
	{
		temp = malloc(2);
		temp[0] = '$';
		temp[1] = '\0';
		return (temp);
	}
	else if (no_q[i] == '$' && no_q[i + 1] == '?')
	{
		status = ft_itoa(g.exit_status);
		return (status);
	}
	return (temp);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helpers2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 20:44:34 by mhassani          #+#    #+#             */
/*   Updated: 2023/06/24 23:54:10 by mhassani         ###   ########.fr       */
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

char	*exit_status(char *no_q)
{
	int i = 0;
	int len = 0;
	char *status;
	if (no_q[i] == '?' && (no_q[i + 1] == ' ' || !no_q[i + 1]))
	{
		status = ft_itoa(g_g.exit_status);
		return (status);
	}
	else if (no_q[i] == '?' && no_q[i + 1] && no_q[i + 1] != ' ')
	{
		while(no_q[i] && no_q[i] != ' ')
		{
			len++;
			i++;
		}
		status = ft_strjoin(ft_itoa(g_g.exit_status), ft_substr(no_q, 1, len - 1));
		return status;
	}
	return (NULL);
}

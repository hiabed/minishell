/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:59:21 by mhassani          #+#    #+#             */
/*   Updated: 2023/07/21 16:19:36 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_compare(char *no_quotes, t_env *envp, char *temp, int *i)
{
	char	*key;

	g_g.value = NULL;
	g_g.result = NULL;
	key = ft_extract_key(no_quotes);
	g_g.value = env_value(envp, key);
	free(key);
	g_g.value = ft_strjoin_f2(g_g.dollars, g_g.value);
	if (!g_g.value)
		g_g.value = if_not_value(no_quotes, g_g.value, i);
	if (!temp)
		g_g.result = ft_strjoin(g_g.chars, g_g.value);
	else
		g_g.result = ft_strjoin(temp, g_g.value);
	temp = g_g.result;
	free(g_g.value);
	return (temp);
}

char	*compare_keys_without_q(t_env *envp, char *no_quotes, int *i,
		char *temp)
{
	g_g.chars = fst_chars(no_quotes, 0);
	g_g.dollars = print_expanded_dollars(&no_quotes[*i]);
	g_g.count = num_dollars(&no_quotes[*i]);
	while (no_quotes[*i] && no_quotes[(*i) + 1] && no_quotes[*i] == '$')
		(*i)++;
	temp = ft_compare(&no_quotes[*i], envp, temp, i);
	if (!temp)
		temp = ft_strjoin(g_g.chars, g_g.dollars);
	free(g_g.chars);
	free(g_g.dollars);
	return (temp);
}

char	*not_compare_keys(char *no_quotes, int *i, char *temp)
{
	char	*dollars;
	char	*ext_key;
	char	*result;
	char	*chars;

	dollars = print_not_expanded_dollars(&no_quotes[*i]);
	ext_key = ft_extract_key(&no_quotes[*i]);
	chars = fst_chars(no_quotes, 0);
	result = NULL;
	dollars = ft_strjoin_f(dollars, ext_key);
	if (!temp)
		result = ft_strjoin(chars, dollars);
	else
		result = ft_strjoin(temp, dollars);
	temp = result;
	while (no_quotes[*i] && no_quotes[*i + 1] && no_quotes[*i] == '$')
		(*i)++;
	free(ext_key);
	free(chars);
	free(dollars);
	return (temp);
}

char	*ft_expand_value(char *no_q, t_env *envp)
{
	int	i;

	i = 0;
	g_g.temp = NULL;
	while (no_q && no_q[i])
	{
		if (no_q[i] == '$')
		{
			if (num_dollars(&no_q[i]) % 2 != 0)
			{
				g_g.tmp = g_g.temp;
				g_g.temp = compare_keys(envp, no_q, &i, g_g.temp);
				free(g_g.tmp);
			}
			else
			{
				g_g.tmp = g_g.temp;
				g_g.temp = not_compare_keys(no_q, &i, g_g.temp);
				free(g_g.tmp);
			}
		}
		else
			i++;
	}
	return (g_g.temp);
}

char	*ft_expand_value_without_q(char *no_q, t_env *envp)
{
	int	i;

	i = 0;
	g_g.temp = NULL;
	while (no_q[i])
	{
		if (no_q[i] == '$')
		{
			if (num_dollars(&no_q[i]) % 2 != 0)
			{
				g_g.tmp = g_g.temp;
				g_g.temp = compare_keys_without_q(envp, no_q, &i, g_g.temp);
				free(g_g.tmp);
			}
			else
			{
				g_g.tmp = g_g.temp;
				g_g.temp = not_compare_keys(no_q, &i, g_g.temp);
				free(g_g.tmp);
			}
		}
		else
			i++;
	}
	return (g_g.temp);
}

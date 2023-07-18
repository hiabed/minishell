/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:59:21 by mhassani          #+#    #+#             */
/*   Updated: 2023/07/18 23:46:09 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_compare(char *no_quotes, t_env *envp, char *temp, int *i)
{
	char	*key;
	char	*status;
	char	*first_is_num;

	g_g.value = NULL;
	g_g.result = NULL;
	g_g.i = 0;
	key = ft_extract_key(no_quotes);
	status = exit_status(no_quotes);
	first_is_num = first_is_number(no_quotes);
	g_g.value = env_value(envp, key);
	free(key);
	if (!g_g.value && g_g.count == 1 && status)
	{
		(*i)++;
		g_g.value = status;
	}
	else if (!g_g.value && g_g.count == 1 && !ft_isalnum(no_quotes[g_g.i]))
		g_g.value = ft_strdup("$");
	else if (!g_g.value && first_is_num)
		g_g.value = first_is_number(no_quotes);
	else if (!g_g.value)
		g_g.value = ft_strdup("");
	g_g.value = ft_strjoin_f2(g_g.dollars, g_g.value);
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
	{
		temp = ft_strjoin(g_g.chars, g_g.dollars);
	}
	free(g_g.chars);
	free(g_g.dollars);
	return (temp);
}

char	*not_compare_keys(char *no_quotes, int *i, char *temp)
{
	char	*dollars;
	char	*value;
	char	*result;
	char	*chars;

	chars = fst_chars(no_quotes, 0);
	value = NULL;
	result = NULL;
	dollars = ft_strjoin(print_not_expanded_dollars(&no_quotes[*i]),
							ft_extract_key(&no_quotes[*i]));
	if (!temp)
		result = ft_strjoin(chars, dollars);
	else
		result = ft_strjoin(temp, dollars);
	temp = result;
	while (no_quotes[*i] && no_quotes[*i + 1] && no_quotes[*i] == '$')
		(*i)++;
	return (temp);
}

char	*ft_expand_value(char *no_q, t_env *envp)
{
	char	*temp;
	char	*tmp;
	int		i;

	i = 0;
	temp = NULL;
	while (no_q[i])
	{
		if (no_q[i] == '$')
		{
			if (num_dollars(&no_q[i]) % 2 != 0)
			{
				tmp = temp;
				temp = compare_keys(envp, no_q, &i, temp);
				free(tmp);
			}
			else
			{
				tmp = temp;
				temp = not_compare_keys(no_q, &i, temp);
				free(tmp);
			}
		}
		else
			i++;
	}
	return (temp);
}

char	*ft_expand_value_without_q(char *no_q, t_env *envp)
{
	char *temp;
	char *tmp;
	int i;

	i = 0;
	temp = NULL;
	while (no_q[i])
	{
		if (no_q[i] == '$')
		{
			if (num_dollars(&no_q[i]) % 2 != 0)
			{
				tmp = temp;
				temp = compare_keys_without_q(envp, no_q, &i, temp);
				free(tmp);
			}
			else
			{
				tmp = temp;
				temp = not_compare_keys(no_q, &i, temp);
				free(tmp);
			}
		}
		else
			i++;
	}
	return (temp);
}
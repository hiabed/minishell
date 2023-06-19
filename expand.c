/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:59:21 by mhassani          #+#    #+#             */
/*   Updated: 2023/06/19 18:30:18 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_extract_key(char *no_q)
{
	int		i;
	int		j;
	char	*var;

	i = 0;
	j = 0;
	while (no_q[i] && no_q[i] != '\'' && no_q[i] != '+' && no_q[i] != '.'
		&& no_q[i] != '$')
		i++;
	var = malloc(i + 1);
	i = 0;
	while (no_q[i] && no_q[i] != '\'' && no_q[i] != '+' && no_q[i] != '.'
		&& no_q[i] != '$' && no_q[i] != ' ')
		var[i++] = no_q[j++];
	var[i] = '\0';
	return (var);
}

char	*compare_keys(char **envp, char *no_quotes, char *chars, int *i,
		char *temp)
{
	int		j;
	char	*dollars;
	char	*value;
	char	*result;

	value = NULL;
	result = NULL;
	dollars = print_expanded_dollars(&no_quotes[*i]);
	while (no_quotes[*i] && no_quotes[(*i) + 1] && no_quotes[*i] == '$')
		(*i)++;
	j = 0;
	while (envp[j])
	{
		if (!ft_strcmp(env_key(envp[j]), ft_extract_key(&no_quotes[*i])))
		{
			value = env_value(envp[j]);     				//mhassani
			value = ft_strjoin(dollars, value);				//$$mhassani
			if (!temp)
				result = ft_strjoin(chars, value);			//aa$mhassani
			else
				result = ft_strjoin(temp, value);
			temp = result;
		}
		j++;
	}
	if (!temp)
	{
		temp = ft_strjoin(chars, dollars);
		temp = ft_strjoin(temp, after_expand(&no_quotes[*i]));
	}
	else if(temp)
		temp = ft_strjoin(temp, after_expand(&no_quotes[*i]));
	else if(after_expand_check(&no_quotes[*i]) && !temp)
		temp = ft_strjoin(temp, after_expand(&no_quotes[*i]));
	return (temp);
}

char	*not_compare_keys(char *no_quotes, char *chars, int *i, char *temp)
{
	char	*dollars;
	char	*value;
	char	*result;

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

char	*only_dollar(char *no_q)
{
	int		i;
	char	*status;

	i = 0;
	if (no_q[i] == '$' && !no_q[i + 1])
		return (NULL);
	else if (no_q[i] == '$' && no_q[i + 1] == '?')
	{
		status = ft_itoa(g.exit_status);
		return (status);
	}
	return (NULL);
}

char	*ft_expand_value(char *no_q, char **envp)
{
	char *temp;
	char *dollars;
	char *chars;
	int i;

	i = 0;
	temp = NULL;
	chars = fst_chars(no_q, i);
	dollars = NULL;
	while (no_q[i])
	{
		if (no_q[i] == '$')
		{
			if (num_dollars(&no_q[i]) % 2 != 0)
				temp = compare_keys(envp, no_q, chars, &i, temp);
			else
				temp = not_compare_keys(no_q, chars, &i, temp);
		}
		i++;
	}
	return (temp);
}
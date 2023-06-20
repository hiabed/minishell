/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:59:21 by mhassani          #+#    #+#             */
/*   Updated: 2023/06/20 17:56:49 by mhassani         ###   ########.fr       */
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

char	*ft_compare(char *no_quotes, char *chars, char **envp, char *temp)
{
	char	*value;
	char	*dollars;
	char	*result;
	int		j;

	dollars = print_expanded_dollars(no_quotes);
	j = 0;
	while (envp[j])
	{
		if (!ft_strcmp(env_key(envp[j]), ft_extract_key(no_quotes)))
		{
			value = env_value(envp[j]);         //mhassani
			value = ft_strjoin(dollars, value); //$$mhassani
			if (!temp)
				result = ft_strjoin(chars, value); //aa$mhassani
			else
				result = ft_strjoin(temp, value);
			temp = result;
			return (temp);
		}
		j++;
	}
	return (NULL);
}

char	*compare_keys(char **envp, char *no_quotes, int *i, char *temp)
{
	char	*dollars;
	char	*chars;

	chars = fst_chars(no_quotes, 0);
	dollars = print_expanded_dollars(&no_quotes[*i]);
	while (no_quotes[*i] && no_quotes[(*i) + 1] && no_quotes[*i] == '$')
		(*i)++;
	temp = ft_compare(&no_quotes[*i], chars, envp, temp);
	if (!temp)
	{
		temp = ft_strjoin(chars, dollars);
		temp = ft_strjoin(temp, after_expand(&no_quotes[*i]));
	}
	else if (temp)
		temp = ft_strjoin(temp, after_expand(&no_quotes[*i]));
	else if (after_expand_check(&no_quotes[*i]) && !temp)
		temp = ft_strjoin(temp, after_expand(&no_quotes[*i]));
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

char	*ft_expand_value(char *no_q, char **envp)
{
	char *temp;
	int i;

	i = 0;
	temp = NULL;
	while (no_q[i])
	{
		if (no_q[i] == '$')
		{
			if (num_dollars(&no_q[i]) % 2 != 0)
				temp = compare_keys(envp, no_q, &i, temp);
			else
				temp = not_compare_keys(no_q, &i, temp);
		}
		i++;
	}
	temp = only_dollar(no_q, temp);
	return (temp);
}
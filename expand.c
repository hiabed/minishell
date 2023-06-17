/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:59:21 by mhassani          #+#    #+#             */
/*   Updated: 2023/06/17 23:11:09 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*print_not_expanded_dollars(char *no_quotes)
{
	int		i;
	int		j;
	char	*print_var;

	i = 0;
	j = 0;
	while (no_quotes[i] && no_quotes[i] == '$')
		i++;
	while (no_quotes[i] && no_quotes[i] != '$')
		i++;
	print_var = malloc(i + 1);
	i = 0;
	while (no_quotes[i] && no_quotes[i] == '$')
		print_var[i++] = no_quotes[j++];
	while (no_quotes[i] && no_quotes[i] != '$')
		print_var[i++] = no_quotes[j++];
	print_var[i] = '\0';
	return (print_var);
}

char	*print_expanded_dollars(char *no_quotes)
{
	int		i;
	int		j;
	char	*print_dollars;

	i = 0;
	j = 0;
	while (no_quotes[i] && no_quotes[i] == '$')
		i++;
	i--;
	print_dollars = malloc(i + 1);
	i = 0;
	while (no_quotes[i] && no_quotes[i] == '$' && no_quotes[i + 1] == '$')
		print_dollars[i++] = no_quotes[j++];
	print_dollars[i] = '\0';
	return (print_dollars);
}

char	*env_key(char *envp)
{
	int		i;
	int		j;
	char	*key;

	i = 0;
	j = 0;
	key = NULL;
	while (envp[i] && envp[i] != '=')
		i++;
	key = malloc(i + 1);
	i = 0;
	while (envp[i] && envp[i] != '=')
		key[j++] = envp[i++];
	key[j] = '\0';
	return (key);
}

char	*env_value(char *envp, char *no_quotes)
{
	int		i;
	int		j;
	int		size;
	char	*value;

	size = 0;
	i = 0;
	j = 0;
	value = NULL;
	while (envp[i] && envp[i] != '=')
		i++;
	i++;
	j = i;
	while (envp[j])
		j++;
	size = j - i;
	value = malloc(size + 1);
	j = 0;
	while (envp[i])
		value[j++] = envp[i++];
	value[j] = '\0';
	value = ft_strjoin(value, after_expand(no_quotes));
	return (value);
}

int	before_dollar_len(char *no_quotes)
{
	int	i;

	i = 0;
	while (no_quotes[i] && no_quotes[i] != '$')
		i++;
	return (i);
}

char	*ft_extract_key(char *no_quotes)
{
	int		i;
	int		j;
	char	*var;

	i = 0;
	j = 0;
	while (no_quotes[i] && no_quotes[i] != '\'' && no_quotes[i] != '+'
		&& no_quotes[i] != '.' && no_quotes[i] != '$')
		i++;
	var = malloc(i + 1);
	i = 0;
	while (no_quotes[i] && no_quotes[i] != '\'' && no_quotes[i] != '+'
		&& no_quotes[i] != '.' && no_quotes[i] != '$')
		var[i++] = no_quotes[j++];
	var[i] = '\0';
	return (var);
}

char	*after_expand(char *no_quotes)
{
	int		i;
	int		j;
	char	*var;
	int		len;

	len = 0;
	i = 0;
	j = 0;
	while (no_quotes[i] && no_quotes[i] != '\'' && no_quotes[i] != '+'
		&& no_quotes[i] != '.')
		i++;
	len = ft_strlen(&no_quotes[i]);
	var = malloc(len + 1);
	while (no_quotes[i] && no_quotes[i] != '$')
		var[j++] = no_quotes[i++];
	var[j] = '\0';
	return (var);
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

char	*ft_expand_value(char *no_quotes, char **envp)
{
	char *chars;
	char *value;
	char *result;
	char *temp;
	char *dollars;
	char *status;
	int i;
	int j;
	int k;

	dollars = NULL;
	temp = NULL;
	i = 0;
	k = 0;
	value = NULL;
	chars = malloc(before_dollar_len(no_quotes) + 1);
	if (no_quotes[i] == '$' && !no_quotes[i + 1])
		return (NULL);
	else if (no_quotes[i] == '$' && no_quotes[i + 1] == '?')
	{
		status = ft_itoa(exit_status);
		return status;
	}
	else if (no_quotes[i] == '$' && no_quotes[i + 1] == '_')
	{
		return NULL;
	}
	while (no_quotes[i] && no_quotes[i] != '$')
		chars[k++] = no_quotes[i++];
	chars[k] = '\0';
	while (no_quotes[i])
	{
		if (no_quotes[i] == '$')
		{
			if (num_dollars(&no_quotes[i]) % 2 != 0)
			{
				dollars = print_expanded_dollars(&no_quotes[i]);
				while (no_quotes[i] && no_quotes[i + 1] && no_quotes[i] == '$')
					i++;
				j = 0;
				while (envp[j])
				{
					if (!ft_strcmp(env_key(envp[j]), ft_extract_key(&no_quotes[i])))
					{
						value = env_value(envp[j], &no_quotes[i]);
						value = ft_strjoin(dollars, value);
						if (!temp)
							result = ft_strjoin(chars, value);
						else
							result = ft_strjoin(temp, value);
						temp = result;
					}
					j++;
				}
			}
			else
			{
				dollars = ft_strjoin(print_not_expanded_dollars(&no_quotes[i]), ft_extract_key(&no_quotes[i]));
				if (!temp)
					result = ft_strjoin(chars, dollars);
				else
					result = ft_strjoin(temp, dollars);
				temp = result;
				while (no_quotes[i] && no_quotes[i + 1] && no_quotes[i] == '$')
					i++;
			}
		}
		i++;
	}
	if(!temp)
	{
		temp = malloc(1);
		temp[0] = '\0';
		temp = ft_strjoin(chars, dollars);
	}
	return (temp);
}
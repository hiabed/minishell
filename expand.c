/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:59:21 by mhassani          #+#    #+#             */
/*   Updated: 2023/06/13 18:05:25 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_key(char *envp)
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

char	*ft_value(char *envp)
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

// int	ft_var_before_quote(char *no_quotes)
// {
// 	int	i;

// 	i = 0;
// 	while (no_quotes[i] && no_quotes[i] != '\'')
// 		i++;
// 	if (no_quotes[i] == '\'')
// 		return (1);
// 	else
// 		return (0);
// 	return (0);
// }

char	*ft_extract_key(char *no_quotes)
{
	int		i;
	int		j;
	char	*var;

	i = 0;
	j = 0;
	while (no_quotes[i] && no_quotes[i] != '\'' && no_quotes[i] != '+'
		&& no_quotes[i] != '.')
		i++;
	var = malloc(i + 1);
	i = 0;
	while (no_quotes[i] && no_quotes[i] != '\'' && no_quotes[i] != '+'
		&& no_quotes[i] != '.')
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
		&& no_quotes[i] != '.') //check for single quote for now, and will add other symbols if needed;
		i++;
	len = ft_strlen(&no_quotes[i]);
	var = malloc(len + 1);
	while (no_quotes[i])
		var[j++] = no_quotes[i++];
	var[j] = '\0';
	return (var);
}

char	*ft_expand_value(char *no_quotes, char **envp)
{
	int		i;
	int		j;
	int		k;
	int		l;
	char	*chars;
	char	*value;
	char	*result;

	l = 0;
	k = 0;
	i = 0;
	j = 0;
	value = NULL;
	chars = malloc(before_dollar_len(no_quotes) + 1);
	if (no_quotes[i] == '$' && !no_quotes[i + 1])
		return (NULL);
	else if (no_quotes[i] == '$' && no_quotes[i + 1] == '?')
	{
		//should handle for exit status;
	}
	else if (no_quotes[i] == '$' && (no_quotes[i + 1] == '+' || no_quotes[i
				+ 1] == '.' || no_quotes[i + 1] == '\''))
		return (NULL);
	while (no_quotes[i])
	{
		if (no_quotes[i] == '$')
		{
			i++;
			l++;
			while (envp[j])
			{
				if (!strcmp(ft_key(envp[j]), ft_extract_key(&no_quotes[i])))
					value = ft_value(envp[j]);
				j++;
			}
			break ;
		}
		else
			chars[k++] = no_quotes[i];
		i++;
	}
	chars[k] = '\0';
	if (!value)
		return (chars);
	result = ft_strjoin(chars, value);
	if (after_expand(&no_quotes[i]))
		result = ft_strjoin(result, after_expand(&no_quotes[i]));
	return (result);
}

char	*ft_expand_key(char *no_quotes, char **envp)
{
	int i = 0;
	int j = 0;
	if (no_quotes[i] == '$' && (no_quotes[i + 1] == '+' || no_quotes[i
			+ 1] == '.'))
		return (NULL);
	else if (no_quotes[i] == '$')
	{
		i++;
		while (envp[j])
		{
			if (!strcmp(ft_key(envp[j]), &no_quotes[i]))
				return (ft_key(envp[j]));
			j++;
		}
	}
	return (NULL);
}
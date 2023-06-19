/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 20:35:28 by mhassani          #+#    #+#             */
/*   Updated: 2023/06/19 17:25:36 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	after_expand_check(char *no_quotes)
{
	int		i;
	int		j;
	int		k;
	int		len;

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

char	*after_expand(char *no_quotes)
{
	int		i;
	int		j;
	int		k;
	char	*var;
	int		len;

	i = 0;
	k = 0;
	len = 0;
	j = 0;
	while (no_quotes[i] && no_quotes[i] != '\'' && no_quotes[i] != '+'
		&& no_quotes[i] != '.' && no_quotes[i] != '$' && no_quotes[i] != ' ')
	{
		k++;
		i++;
	}
	while (no_quotes[k] && no_quotes[k] != '$')
	{
		k++;
		len++;
	}
	var = malloc(len + 1);
	while (no_quotes[i] && no_quotes[i] != '$')
		var[j++] = no_quotes[i++];
	var[j] = '\0';
	return (var);
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

char	*env_value(char *envp)
{
	int i;
	int j;
	int size;
	char *value;
	
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
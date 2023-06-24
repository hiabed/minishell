/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 20:35:28 by mhassani          #+#    #+#             */
/*   Updated: 2023/06/24 18:48:10 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_value(t_env *a, char *s)
{
	while (a)
	{
		if (ft_strcmp(a->key, s) == 0)
			return (a->valuer);
		a = a->next;
	}
	return (NULL);
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

char	*after_expand(char *no_quotes)
{
	char		*var;
	t_expand	exp;

	exp.i = 0;
	exp.k = 0;
	exp.len = 0;
	exp.j = 0;
	while (no_quotes[exp.i] && no_quotes[exp.i] != '\''
		&& no_quotes[exp.i] != '+' && no_quotes[exp.i] != '.'
		&& no_quotes[exp.i] != '$' && no_quotes[exp.i] != ' ')
	{
		exp.k++;
		exp.i++;
	}
	while (no_quotes[exp.k] && no_quotes[exp.k] != '$')
	{
		exp.k++;
		exp.len++;
	}
	var = malloc(exp.len + 1);
	while (no_quotes[exp.i] && no_quotes[exp.i] != '$')
		var[exp.j++] = no_quotes[exp.i++];
	var[exp.j] = '\0';
	return (var);
}

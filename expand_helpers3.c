/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helpers3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:23:15 by mhassani          #+#    #+#             */
/*   Updated: 2023/07/19 17:45:51 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*first_is_number(char *no_quotes)
{
	int		i;
	int		j;
	char	*str;

	if (ft_isdigit(no_quotes[0]))
	{
		i = 0;
		j = 0;
		while (no_quotes[i] && (no_quotes[i] != ' ' && no_quotes[i] != '\t'))
			i++;
		str = malloc(i + 1);
		i = 1;
		while (no_quotes[i] && (no_quotes[i] != ' ' && no_quotes[i] != '\t'))
			str[j++] = no_quotes[i++];
		str[i - 1] = '\0';
		return (str);
	}
	return (NULL);
}

char	*ft_extract_key(char *no_q)
{
	int		i;
	int		j;
	char	*var;

	i = 0;
	j = 0;
	while (no_q[i] && ft_isalnum_expand(no_q[i]))
		i++;
	var = malloc(i + 1);
	i = 0;
	while (no_q[i] && ft_isalnum_expand(no_q[i]) && no_q[i] != ' ')
		var[i++] = no_q[j++];
	var[i] = '\0';
	return (var);
}

char	*compare_keys(t_env *envp, char *no_quotes, int *i, char *temp)
{
	char	*after_exp;

	g_g.chars = fst_chars(no_quotes, 0);
	g_g.dollars = print_expanded_dollars(&no_quotes[*i]);
	g_g.count = num_dollars(&no_quotes[*i]);
	while (no_quotes[*i] && no_quotes[(*i) + 1] && no_quotes[*i] == '$')
		(*i)++;
	temp = ft_compare(&no_quotes[*i], envp, temp, i);
	after_exp = after_expand(&no_quotes[*i]);
	if (!temp)
	{
		temp = ft_strjoin(g_g.chars, g_g.dollars);
		temp = ft_strjoin_f(temp, after_exp);
	}
	else if (temp)
		temp = ft_strjoin_f(temp, after_exp);
	else if (after_expand_check(&no_quotes[*i]) && !temp)
		temp = ft_strjoin_f(temp, after_exp);
	free(after_exp);
	free(g_g.chars);
	free(g_g.dollars);
	return (temp);
}

char	*if_not_value(char *no_quotes, char *value, int *i)
{
	char	*first_is_num;
	char	*status;

	g_g.i = 0;
	first_is_num = first_is_number(no_quotes);
	status = exit_status(no_quotes);
	if (!value && g_g.count == 1 && status)
	{
		(*i)++;
		value = status;
	}
	else if (!value && g_g.count == 1 && !ft_isalnum(no_quotes[g_g.i + 1]))
	{
		(*i)++;
		value = ft_strdup("$");
	}
	else if (!value && first_is_num)
		value = first_is_number(no_quotes);
	else if (!value)
		value = ft_strdup("");
	return (value);
}

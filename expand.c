/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:59:21 by mhassani          #+#    #+#             */
/*   Updated: 2023/07/08 18:33:52 by mhassani         ###   ########.fr       */
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
		&& no_q[i] != '$' && no_q[i] != ' ' && no_q[i] != '\n')
		i++;
	var = malloc(i + 1);
	i = 0;
	while (no_q[i] && no_q[i] != '\'' && no_q[i] != '+' && no_q[i] != '.'
		&& no_q[i] != '$' && no_q[i] != ' ' && no_q[i] != '\n')
		var[i++] = no_q[j++];
	var[i] = '\0';
	return (var);
}

char	*ft_compare(char *no_quotes, t_env *envp, char *temp)
{
	char	*extract_key;
	char	*exit_stat;

	g_g.result = NULL;
	extract_key = ft_extract_key(no_quotes);
	exit_stat = exit_status(no_quotes);
	g_g.i = 0;
	g_g.value = env_value(envp, extract_key);
	free(extract_key);
	if (!g_g.value && g_g.count == 1 && exit_status(no_quotes))
	{
		g_g.value = exit_stat;
	}
	else if (!g_g.value && g_g.count == 1 && !ft_isalnum(no_quotes[g_g.i]))
	{
		g_g.value = malloc(2);
		g_g.value[0] = '$';
		g_g.value[1] = '\0';
	}
	else if (!g_g.value)
	{
		g_g.value = malloc(1);
		g_g.value[0] = '\0';
	}
	g_g.value = ft_strjoin_f(g_g.dollars, g_g.value);
	if (!temp)
		g_g.result = ft_strjoin_f(g_g.chars, g_g.value);
	else
		g_g.result = ft_strjoin_f(temp, g_g.value);
	temp = g_g.result;
	return (temp);
}

char	*compare_keys(t_env *envp, char *no_quotes, int *i, char *temp)
{
	printf("----------------file %s line %d, %p\n",__FILE__, __LINE__, no_quotes);
	g_g.chars = fst_chars(no_quotes, 0);                  //!
	g_g.dollars = print_expanded_dollars(&no_quotes[*i]); //!
	g_g.count = num_dollars(&no_quotes[*i]);              //done
	
	while (no_quotes[*i] && no_quotes[(*i) + 1] && no_quotes[*i] == '$')
	{
		free(&no_quotes[*i]);
		(*i)++;
	}
	temp = ft_compare(&no_quotes[*i], envp, temp);
	if (!temp)
	{
		temp = ft_strjoin_f(g_g.chars, g_g.dollars);
		temp = ft_strjoin_f(temp, after_expand(&no_quotes[*i]));
	}
	else if (temp)
		temp = ft_strjoin_f(temp, after_expand(&no_quotes[*i]));
	else if (after_expand_check(&no_quotes[*i]) && !temp)
		temp = ft_strjoin_f(temp, after_expand(&no_quotes[*i]));
	return (temp);
}

char	*not_compare_keys(char *no_quotes, int *i, char *temp)
{
	char	*dollars;
	char	*result;
	char	*chars;

	printf("----------------file %s line %d, %p\n",__FILE__, __LINE__, no_quotes);
	chars = fst_chars(no_quotes, 0);
	result = NULL;
	dollars = ft_strjoin_f(print_not_expanded_dollars(&no_quotes[*i]),
							ft_extract_key(&no_quotes[*i]));
	if (!temp)
		result = ft_strjoin_f(chars, dollars);
	else
		result = ft_strjoin_f(temp, dollars);
	temp = result;
	while (no_quotes[*i] && no_quotes[*i + 1] && no_quotes[*i] == '$')
	{
		(*i)++;
	}
	return (temp);
}

char	*ft_expand_value(char *no_q, t_env *envp)
{
	char	*temp;
	int		i;

	i = 0;
	temp = NULL;
	while (no_q[i])
	{
		if (no_q[i] == '~' || (no_q[i] == '~' && no_q[i + 1] == '/'))
			temp = get_env(&envp, "HOME");
		else if (no_q[i] == '$')
		{
			if (!g_g.expand && num_dollars(&no_q[i]) % 2 != 0)
			{
				temp = compare_keys(envp, no_q, &i, temp);
			}
			else
				temp = not_compare_keys(no_q, &i, temp);
		}
		i++;
	}
	return (temp);
}

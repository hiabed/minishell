/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:59:21 by mhassani          #+#    #+#             */
/*   Updated: 2023/07/09 22:29:55 by mhassani         ###   ########.fr       */
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
	g_g.result = NULL;
	g_g.i = 0;
	char *key = ft_extract_key(no_quotes);
	char *status = exit_status(no_quotes);
	g_g.value = env_value(envp, key);
	
	if (!g_g.value && g_g.count == 1 && exit_status(no_quotes))
	{
		g_g.value = status;
		free(status);
	}
	else if (!g_g.value && g_g.count == 1 && !ft_isalnum(no_quotes[g_g.i]))
	{
		g_g.value = ft_strdup("$");
	}
	else if (!g_g.value)
	{
		g_g.value = ft_strdup("");
	}
	g_g.value = ft_strjoin(g_g.dollars, g_g.value);
	if (!temp)
	{
		g_g.result = ft_strjoin(g_g.chars, g_g.value);
	}
	else
	{
		g_g.result = ft_strjoin(temp, g_g.value);
	}
	temp = g_g.result;
	free(g_g.value);
	printf("g_g.result: ===> file : %s, line : %d, adress: %p\n", __FILE__, __LINE__, g_g.result);
	return (temp);
}

char	*compare_keys(t_env *envp, char *no_quotes, int *i, char *temp)
{
	g_g.chars = fst_chars(no_quotes, 0);//!
	g_g.dollars = print_expanded_dollars(&no_quotes[*i]); //!
	g_g.count = num_dollars(&no_quotes[*i]); //done
	while (no_quotes[*i] && no_quotes[(*i) + 1] && no_quotes[*i] == '$')
	{
		(*i)++;
	}
	temp = ft_compare(&no_quotes[*i], envp, temp);
	char *after_exp = after_expand(&no_quotes[*i]);
	if (!temp)
	{
		temp = ft_strjoin(g_g.chars, g_g.dollars);
		free(g_g.chars);
		free(g_g.dollars);
		temp = ft_strjoin(temp, after_exp);
	}
	else if (temp)
		temp = ft_strjoin(temp, after_exp);
	else if (after_expand_check(&no_quotes[*i]) && !temp)
		temp = ft_strjoin(temp, after_exp);
	free(after_exp);
	// printf("g_g.chars: ===> file : %s, line : %d, adress: %p\n", __FILE__, __LINE__, g_g.chars);
	return (temp);
}

char	*compare_keys_without_q(t_env *envp, char *no_quotes, int *i, char *temp)
{
	g_g.chars = fst_chars(no_quotes, 0);//!
	g_g.dollars = print_expanded_dollars(&no_quotes[*i]); //!
	g_g.count = num_dollars(&no_quotes[*i]); //done
	while (no_quotes[*i] && no_quotes[(*i) + 1] && no_quotes[*i] == '$')
	{
		(*i)++;
	}
	temp = ft_compare(&no_quotes[*i], envp, temp);
	if (!temp)
	{
		temp = ft_strjoin(g_g.chars, g_g.dollars);
		free(g_g.chars);
		free(g_g.dollars);
	}
	return (temp);
}

char	*not_compare_keys(char *no_quotes, int *i, char *temp)
{
	char	*dollars;
	char	*result;
	char	*chars;

	chars = fst_chars(no_quotes, 0);
	result = NULL;
	char *print_ned = print_not_expanded_dollars(&no_quotes[*i]);
	char *extract_key = ft_extract_key(&no_quotes[*i]);
	dollars = ft_strjoin(print_ned, extract_key);
	if (!temp)
		result = ft_strjoin(chars, dollars);
	else
		result = ft_strjoin(temp, dollars);
	temp = result;
	while (no_quotes[*i] && no_quotes[*i + 1] && no_quotes[*i] == '$')
		(*i)++;
	free(dollars);
	free(chars);
	// free(result);
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
		if(no_q[i] == '~' || (no_q[i] == '~' && no_q[i + 1] == '/'))
			temp = get_env(&envp, "HOME");
		else if (no_q[i] == '$')
		{
			if (!g_g.expand && num_dollars(&no_q[i]) % 2 != 0)
			{
				temp = compare_keys(envp, no_q, &i, temp);
			}
			else
			{
				temp = not_compare_keys(no_q, &i, temp);
			}
		}
		i++;
	}
	printf("no_q: ===> file : %s, line : %d, adress: %p\n", __FILE__, __LINE__, no_q);
	// free(g_g.result);
	// free(g_g.value);
	// free(g_g.dollars);
	// free(g_g.chars);
	return (temp);
}

char	*ft_expand_value_without_q(char *no_q, t_env *envp)
{
	char	*temp;
	int		i;
	
	i = 0;
	temp = NULL;
	while (no_q[i])
	{
		if(no_q[i] == '~' || (no_q[i] == '~' && no_q[i + 1] == '/'))
			temp = get_env(&envp, "HOME");
		if (no_q[i] == '$')
		{
			if (!g_g.expand && num_dollars(&no_q[i]) % 2 != 0)
			{
				temp = compare_keys_without_q(envp, no_q, &i, temp);
			}
			else
			{
				temp = not_compare_keys(no_q, &i, temp);
			}
		}
		i++;
	}
	printf("temp: ===> file : %s, line : %d, adress: %p\n", __FILE__, __LINE__, temp);
	// free(no_q);
	// free(g_g.result);
	// free(g_g.value);
	// free(g_g.dollars);
	// free(g_g.chars);
	return (temp);
}

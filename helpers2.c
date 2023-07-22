/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 14:07:50 by mhassani          #+#    #+#             */
/*   Updated: 2023/07/21 16:02:37 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	empty_string_condition(char *words, int *i)
{
	if ((words[*i] == '\"' && words[*i + 1] == '\"') || (words[*i] == '\''
			&& words[*i + 1] == '\''))
		return (1);
	return (0);
}

void	lim_check(char *words)
{
	if (words[0] == '\'' || words[0] == '\"')
		g_g.check = 1;
	else
		g_g.check = 0;
}

int	ft_number_type(char *words)
{
	if (words[0] == '<' && words[1] == '<')
		return (4);
	else if (words[0] == '>' && words[1] == '>')
		return (3);
	else if (words[0] == '<')
		return (2);
	else if (words[0] == '>')
		return (1);
	return (0);
}

void	pipe_error(t_data *data, int i)
{
	if (i == 0)
	{
		write(2, "bash: syntax error near unexpected token `|'\n", 45);
		g_g.exit_status = 258;
		data->error++;
	}
	if (i == 1)
	{
		write(2, "minishell: syntax error: unexpected end of file\n", 48);
		g_g.exit_status = 258;
		data->error++;
	}
	if (i == 2)
	{
		write(2, "minishell: unexpected EOF while looking for matching `''\n",
			57);
		write(2, "minishell: syntax error: unexpected end of file\n", 48);
		g_g.exit_status = 258;
		data->error++;
	}
}

char	*fill_expand_without_q(char *str, t_env *envp)
{
	int		i;
	int		j;
	int		size;
	char	*expand;
	char	*exp;

	expand = NULL;
	exp = ft_expand_value_without_q(str, envp);
	if (exp)
	{
		i = 0;
		j = 0;
		size = (ft_strlen(exp) + 1);
		expand = exp;
		free(str);
		str = NULL;
		str = malloc(size);
		while (expand[j])
			str[i++] = expand[j++];
		str[i] = '\0';
	}
	free(expand);
	return (str);
}

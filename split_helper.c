/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 22:03:03 by mhassani          #+#    #+#             */
/*   Updated: 2023/07/18 23:43:08 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	p_in_double_quotes(char *cmd)
{
	int	i;

	i = 0;
	(i)++;
	while (cmd[i] && cmd[i] != '\"')
	{
		if (cmd[i] == '|')
			cmd[i] = -1;
		(i)++;
	}
	if (cmd[i] && cmd[i + 1] && cmd[i] == '\"')
		(i)++;
}

void	s_in_double_quotes(char *token)
{
	int	i;

	i = 0;
	(i)++;
	while (token[i] && token[i] != '\"')
	{
		if (token[i] == ' ')
			token[i] = -2;
		(i)++;
	}
	if (token[i] && token[i + 1] && token[i] == '\"')
		(i)++;
}

void	r_in_double_quotes(char *cmd, int *i)
{
	(*i)++;
	while (cmd[*i] && cmd[*i] != '\"')
	{
		if (cmd[*i] == '>')
			cmd[*i] = -1;
		else if (cmd[*i] == '<')
			cmd[*i] = -2;
		else if (cmd[*i] == '>' && cmd[*i + 1] == '>')
		{
			cmd[(*i)++] = -3;
			cmd[*i] = -3;
		}
		else if (cmd[*i] == '<' && cmd[*i + 1] == '<')
		{
			cmd[(*i)++] = -4;
			cmd[*i] = -4;
		}
		(*i)++;
	}
	if (cmd[*i] && cmd[*i] == '\"')
		(*i)++;
	if (!cmd[*i])
		return ;
}

void	r_in_single_quotes(char *cmd, int *i)
{
	(*i)++;
	while (cmd[*i] && cmd[*i] != '\'')
	{
		if (cmd[*i] == '>')
			cmd[*i] = -1;
		else if (cmd[*i] == '<')
			cmd[*i] = -2;
		else if (cmd[*i] == '>' && cmd[*i + 1] == '>')
		{
			cmd[(*i)++] = -3;
			cmd[*i] = -3;
		}
		else if (cmd[*i] == '<' && cmd[*i + 1] == '<')
		{
			cmd[(*i)++] = -4;
			cmd[*i] = -4;
		}
		(*i)++;
	}
	if (cmd[*i] && cmd[*i] == '\'')
		(*i)++;
	if (!cmd[*i])
		return ;
}

void	replace_red_in_quotes(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\"')
			r_in_double_quotes(cmd, &i);
		else if (cmd[i] == '\'')
			r_in_single_quotes(cmd, &i);
		i++;
	}
}

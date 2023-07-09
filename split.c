/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:34:41 by mhassani          #+#    #+#             */
/*   Updated: 2023/07/06 19:07:50 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_pipe_in_quotes(char *cmd)
{
	g_g.i = 0;
	while (cmd[g_g.i])
	{
		if (cmd[g_g.i] == '\"')
		{
			p_in_double_quotes(&cmd[g_g.i]);
			increment_i(cmd, &g_g.i);
		}
		else if (cmd[g_g.i] == '\'')
		{
			g_g.i++;
			while (cmd[g_g.i] && cmd[g_g.i] != '\'')
			{
				if (cmd[g_g.i] == '|')
					cmd[g_g.i] = -1;
				g_g.i++;
			}
			if (cmd[g_g.i] && cmd[g_g.i] == '\'')
				g_g.i++;
			if (!cmd[g_g.i])
				break ;
		}
		else
			g_g.i++;
	}
}

char	**split_with_pipe(char *cmd)
{
	char	**token;
	int		i;
	int		j;

	i = 0;
	j = 0;
	token = ft_split(cmd, '|');
	while (token[j])
	{
		i = 0;
		while (token[j][i])
		{
			if (token[j][i] == -1)
				token[j][i] = '|';
			i++;
		}
		j++;
	}
	return (token);
}

void	replace_space_in_quotes(char *token)
{
	g_g.i = 0;
	while (token[g_g.i])
	{
		if (token[g_g.i] == '\"')
		{
			s_in_double_quotes(&token[g_g.i]);
			increment_i(token, &g_g.i);
		}
		else if (token[g_g.i] == '\'')
		{
			g_g.i++;
			while (token[g_g.i] && token[g_g.i] != '\'')
			{
				if (token[g_g.i] == ' ')
					token[g_g.i] = -2;
				g_g.i++;
			}
			if (token[g_g.i] && token[g_g.i] == '\'')
				g_g.i++;
			if (!token[g_g.i])
				break ;
		}
		else
			g_g.i++;
	}
}

char	**split_with_space(char *token)
{
	char	**words;
	int		i;
	int		j;

	i = 0;
	j = 0;
	words = ft_split_space(token);
	while (words[j])
	{
		i = 0;
		while (words[j][i])
		{
			if (words[j][i] == -2)
				words[j][i] = ' ';
			i++;
		}
		j++;
	}
	return (words);
}

void	bring_back(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == -1)
			cmd[i] = '>';
		else if (cmd[i] == -2)
			cmd[i] = '<';
		else if (cmd[i] == -3)
		{
			cmd[i++] = '>';
			cmd[i] = '>';
		}
		else if (cmd[i] == -4)
		{
			cmd[i++] = '<';
			cmd[i] = '<';
		}
		else if (!cmd[i])
			break ;
		i++;
	}
}

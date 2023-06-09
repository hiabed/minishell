/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:34:41 by mhassani          #+#    #+#             */
/*   Updated: 2023/06/09 19:14:21 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_pipe_in_quotes(char *cmd)
{
	int	i;

	i = 0;
	printf("%s\n", cmd);
	while (cmd[i])
	{
		if (cmd[i] == 34 || cmd[i] == 39)
		{
			i++;
			while (cmd[i] && cmd[i] != 34 && cmd[i] != 39)
			{
				if (cmd[i] == '|')
					cmd[i] = -1;
				i++;
			}
			if (cmd[i] && (cmd[i] == 34 || cmd[i] == 39))
				i++;
			if (!cmd[i])
			{
				printf("sdfdfhjkjk\n");
				break ;
			}
		}
		else
			i++;
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
	int	i;

	i = 0;
	// printf("token: %s\n", token);
	while (token[i])
	{
		if (token[i] == 34 || token[i] == 39)
		{
			i++;
			while (token[i] && token[i] != 34 && token[i] != 39)
			{
				if (token[i] == ' ')
					token[i] = -2;
				i++;
			}
			if (token[i] && (token[i] == 34 || token[i] == 39))
				i++;
			if (!token[i])
				break ;
		}
		else
			i++;
	}
	
}

char	**split_with_space(char *token)
{
	char	**words;
	int		i;
	int		j;

	i = 0;
	j = 0;
	words = ft_split(token, ' ');
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

void	replace_red_in_quotes(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == 34 || cmd[i] == 39)
		{
			i++;
			while (cmd[i] && cmd[i] != 34 && cmd[i] != 39)
			{
				if (cmd[i] == '>')
					cmd[i] = -1;
				if(cmd[i] == '<')
					cmd[i] = -2;
				if (cmd[i] == '>' && cmd[i + 1] == '>')
				{
					cmd[i++] = -3;
					cmd[i] = -3;
				}
				if (cmd[i] == '<' && cmd[i + 1] == '<')
				{
					cmd[i++] = -4;
					cmd[i] = -4;
				}
				i++;
			}
			if (cmd[i] && (cmd[i] == 34 || cmd[i] == 39))
				i++;
			if (!cmd[i])
				break ;
		}
		i++;
	}
}

void	bring_back(char *cmd)
{
	int		i;

	i = 0;
	while (cmd)
	{
		i = 0;
		while (cmd[i])
		{
			if (cmd[i] == -1)
				cmd[i] = '>';
			if (cmd[i] == -2)
				cmd[i] = '<';
			if (cmd[i] == -3)
			{
				cmd[i++] = '>';
				cmd[i] = '>';
			}
			if (cmd[i] == -4)
			{
				cmd[i++] = '<';
				cmd[i] = '<';
			}
			if(!cmd[i])
				break;
			i++;
		}
	}
}
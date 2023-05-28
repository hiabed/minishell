/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:34:41 by mhassani          #+#    #+#             */
/*   Updated: 2023/05/28 21:54:30 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void replace_red(char *cmd)
{
    int i = 0;
	ft_strdup(cmd);
    while (cmd[i])
    {
        if (cmd[i] == 34 || cmd[i] == 39)
        {
            i++;
            while (cmd[i] && cmd[i] != 34 && cmd[i] != 39)
                i++;
            if (cmd[i] && (cmd[i] == 34 || cmd[i] == 39))
                i++;
        }
        if (cmd[i] && (cmd[i] == '>' || cmd[i] == '<'))
        {
			
        }
        i++;
    }
}

void	replace_pipe_in_quotes(char *cmd)
{
	int	i;

	i = 0;
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
		}
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
		while (token[j][i] && token[j][i] != '|')
		{
			if (token[j][i] == -1)
				token[j][i] = '|';
			i++;
		}
		j++;
	}
	return (token);
}

void	replace_space_in_quotes(char *tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i] == 34 || tokens[i] == 39)
		{
			i++;
			while (tokens[i] && tokens[i] != 34 && tokens[i] != 39)
			{
				if (tokens[i] == ' ')
					tokens[i] = -2;
				i++;
			}
			if (tokens[i] && (tokens[i] == 34 || tokens[i] == 39))
				i++;
			if (!tokens[i])
				break ;
		}
		i++;
	}
}

char	**split_with_space(char *token)
{
	char **words;
	int i;
	int j;

	i = 0;
	j = 0;
	words = ft_split(token, ' ');
	while (words[j])
	{
		i = 0;
		if (words[j][i] == 34 || words[j][i] == 39)
		{
			while (words[j][i] && words[j][i] != ' ')
			{
				words[j][i] = words[j][i + 1];
				if (words[j][i] == -2)
					words[j][i] = ' ';
				i++;
			}
			words[j][i - 2] = '\0';
		}
		else
			j++;
	}
	return (words);
}
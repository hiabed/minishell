/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:53:19 by mhassani          #+#    #+#             */
/*   Updated: 2023/05/26 22:28:27 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_pipe_in_cotes(char *cmd)
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

void	replace_space_in_cotes(char *tokens)
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
			if(!tokens[i])
				break;
		}
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
		while (words[j][i] && words[j][i] != ' ')
		{
			if (words[j][i] == -2)
				words[j][i] = ' ';
			i++;
		}
		j++;
	}
	return (words);
}

int	main(void)
{
	char	*cmd;
	t_data	*data;
	char	**tokens;
	char	**words;
	int		i;
	int j;

	data = malloc(sizeof(t_data));
	while (1)
	{
		cmd = readline("minishell-3.2$ ");
		if (!cmd)
		{
			printf("exit\n");
			exit(EXIT_FAILURE);
		}
		add_history(cmd);
		data->error = 0;
		syntax_errors(cmd, data);
		replace_pipe_in_cotes(cmd);
		tokens = split_with_pipe(cmd);
		j = 0;
		while(tokens[j])
		{
			printf("====>\n");	
			replace_space_in_cotes(tokens[j]);
			words = split_with_space(tokens[j]);
			i = 0;
			while(words[i])
			{
				printf("words[%d]: %s\n", i, words[i]);
				i++;
			}
			j++;
		}
		// Free the memory allocated by readline;
		free(cmd);
	}
	return (0);
}

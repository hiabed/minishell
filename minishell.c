/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:53:19 by mhassani          #+#    #+#             */
/*   Updated: 2023/05/26 18:38:37 by mhassani         ###   ########.fr       */
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

void	replace_space_in_cotes(char *cmd)
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
				if (cmd[i] == ' ')
					cmd[i] = -2;
				i++;
			}
			if (cmd[i] && (cmd[i] == 34 || cmd[i] == 39))
				i++;
		}
		i++;
	}
}

void	split_with_space(char *cmd)
{
	char	**token;
	char	**words;
	int		i;
	int		j;
	int		k;

	k = 0;
	i = 0;
	j = 0;
	token = split_with_pipe(cmd);
		//===> [0]echo "hello-2world" <===| [1]cat-e Makefile
	while (token[j])
	{
		words = ft_split(token[j], ' ');
		while (words[j])
		{
			printf("token[%d]: %s\n", j, words[j]);
			j++;
		}
		j++;
	}
	j = 0;
	while (token[j])
	{
		i = 0;
		while (token[j][i] && token[j][i] != ' ')
		{
			if (token[j][i] == -2)
				token[j][i] = ' ';
			i++;
		}
		j++;
	}

	j = 0; //freeing memory;
	while (words[j])
	{
		free(words[j]);
		j++;
	}
	free(words);
}

int	main(void)
{
	char	*cmd;
	t_data	*data;

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
		split_with_pipe(cmd);
		replace_space_in_cotes(cmd);
		split_with_space(cmd);
		// Free the memory allocated by readline;
		free(cmd);
	}
	return (0);
}

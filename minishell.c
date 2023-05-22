/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:53:19 by mhassani          #+#    #+#             */
/*   Updated: 2023/05/22 21:28:55 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_syntax_errors(char *cmd, int i)
{
	int	error;

	error = 0;
	i = 0;
	while (cmd[i] == ' ' || cmd[i] == '\t')
		i++;
	if (cmd[i] == '|')
	{
		write(2, "minishell: syntax error\n", 24);
		error++;
	}
	while (cmd[i])
	{
		if (cmd[i] == '|')
		{
			while (cmd[i + 1] == ' ' || cmd[i + 1] == '\t')
				i++;
			if ((cmd[i + 1] == '\0' || cmd[i + 1] == '|') && !error)
			{
				write(2, "minishell: syntax error\n", 24);
				break ;
			}
		}
		i++;
	}
}

void	red_syntax_errors(char *cmd, int i)
{
	int error;
	
	i = 0;
	error = 0;
	while (cmd[i] == ' ' || cmd[i] == '\t')
		i++;
	if ((cmd[i] == '>' || cmd[i] == '<') && (cmd[i + 1] == '>' || cmd[i
			+ 1] == '<') && (cmd[i + 2] == '>' || cmd[i + 2] == '<'))
	{
		write(2, "minishell: syntax error\n", 24);
		error++;
	}
		while (cmd[i])
		{
			if ((cmd[i] == '>' || cmd[i] == '<') && (cmd[i + 1] != '>' && cmd[i
					+ 1] != '<'))
			{
				while (cmd[i + 1] == ' ' || cmd[i + 1] == '\t')
					i++;
				if ((cmd[i + 1] == '\0' || cmd[i + 1] == '>' || cmd[i
					+ 1] == '<' || cmd[i + 1] == '|') && !error)
				{
					write(2, "minishell: syntax error\n", 24);
					break ;
				}
			}
			i++;
		}
}

int	main(void)
{
	char	*cmd;
	char	**token;
	int		i;
	int		len;

	len = 0;
	// Loop until the user enters "exit"
	while (1)
	{
		cmd = readline("minishell-3.2$ ");
		if (!cmd)
		{
			printf("exit\n");
			exit(EXIT_FAILURE);
		}
		add_history(cmd);
		//printf("the cmd is: %s\n", cmd);
		pipe_syntax_errors(cmd, i);
		red_syntax_errors(cmd, i);
		token = ft_split(cmd, '|');
		i = 0;
		while (token[i])
		{
			printf("token [%d]: %s\n", i, token[i]);
			i++;
		}
		i = 0;
		while (token[i])
		{
			free(token[i]);
			i++;
		}
		free(token);
		// Free the memory allocated by readline
		free(cmd);
	}
	return (0);
}

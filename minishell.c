/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:53:19 by mhassani          #+#    #+#             */
/*   Updated: 2023/05/23 14:46:09 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_syntax_errors(char *cmd, t_data *data)
{
	int i;
	
	data->error = 0;
	i = 0;
	while (cmd[i] == ' ' || cmd[i] == '\t')
		i++;
	if (cmd[i] == '|')
	{
		write(2, "minishell: syntax error\n", 24);
		data->error++;
	}
	while (cmd[i])
	{
		if (cmd[i] == '|')
		{
			while (cmd[i + 1] == ' ' || cmd[i + 1] == '\t')
				i++;
			if ((cmd[i + 1] == '\0' || cmd[i + 1] == '|' || cmd[i + 3] == '>' || cmd[i + 3] == '<') && !data->error)
			{
				write(2, "minishell: syntax error\n", 24);
				data->error++;
				break ;
			}
		}
		i++;
	}
}

void	red_syntax_errors(char *cmd, t_data *data)
{
	int i;
	
	i = 0;
	while (cmd[i] == ' ' || cmd[i] == '\t')
		i++;
	if ((cmd[i] == '>' || cmd[i] == '<') && (cmd[i + 1] == '>' || cmd[i
			+ 1] == '<') && (cmd[i + 2] == '>' || cmd[i + 2] == '<') && !data->error)
	{
		write(2, "minishell: syntax error\n", 24);
		data->error++;
	}
		while (cmd[i])
		{
			if ((cmd[i] == '>' || cmd[i] == '<') && (cmd[i + 1] != '>' && cmd[i
					+ 1] != '<'))
			{
				while (cmd[i + 1] == ' ' || cmd[i + 1] == '\t')
					i++;
				if ((cmd[i + 1] == '\0' || cmd[i + 1] == '>' || cmd[i
					+ 1] == '<' || cmd[i + 1] == '|') && !data->error)
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
	// char	**token;
	int		len;
	t_data	*data;
	
	data = malloc(sizeof(t_data));
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
		pipe_syntax_errors(cmd, data);
		red_syntax_errors(cmd, data);
		// token = ft_split(cmd, '|');
		// i = 0;
		// while (token[i])
		// {
		// 	printf("token [%d]: %s\n", i, token[i]);
		// 	i++;
		// }
		// i = 0;
		// while (token[i])
		// {
		// 	free(token[i]);
		// 	i++;
		// }
		// free(token);
		// Free the memory allocated by readline
		free(cmd);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:53:19 by mhassani          #+#    #+#             */
/*   Updated: 2023/05/24 13:49:55 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_syntax_errors(char *cmd, t_data *data)
{
	int	i;

	i = 0;
	data->error = 0;
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
			if ((cmd[i + 1] == '\0' || cmd[i + 1] == '|' || cmd[i + 3] == '>'
					|| cmd[i + 3] == '<') && !data->error)
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
	int	i;

	i = 0;
	data->error = 0;
	while (cmd[i] == ' ' || cmd[i] == '\t')
		i++;
	if ((cmd[i] == '>' || cmd[i] == '<') && (cmd[i + 1] == '>' || cmd[i
			+ 1] == '<') && (cmd[i + 2] == '>' || cmd[i + 2] == '<')
		&& !data->error)
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
			if ((cmd[i + 1] == '\0' || cmd[i + 1] == '>' || cmd[i + 1] == '<'
					|| cmd[i + 1] == '|') && !data->error)
			{
				write(2, "minishell: syntax error\n", 24);
				break ;
			}
		}
		i++;
	}
}

// void	dcotes_syntax_errors(char *cmd, t_data *data)
// {
// 	int	i;
// 	int	dcotes;

// 	i = 0;
// 	dcotes = 0;
// 	while (cmd[i])
// 	{
// 		while (cmd[i] && cmd[i] != 34)
// 			i++;
// 		if (cmd[i] == 34)
// 		{
// 			dcotes++;
// 			i++;
// 		}
// 		if (cmd[i] == '\0' && (dcotes % 2 == 1) && !data->error)
// 		{
// 			write(2, "minishell: syntax error\n", 24);
// 			break ;
// 		}
// 	}
// }

// void	dcotes_syntax_errors(char *cmd, t_data *data)
// {
// 	int	i;
// 	int	dcotes;

// 	i = 0;
// 	dcotes = 0;
// 	data->error = 0;
// 	while (cmd[i])
// 	{
// 		while (cmd[i] && cmd[i] != 39 && cmd[i] != 34)
// 			i++;
// 		if (cmd[i] == 39)      //(');
// 		{
// 			if (cmd[i] == 34)    //(");
// 				i++;
// 		}
// 		if (cmd[i] == 39)       //(');
// 		{
// 			dcotes++;
// 			i++;
// 		}
// 		if (cmd[i] == '\0' && (dcotes % 2 == 1) && !data->error)
// 		{
// 			write(2, "minishell: syntax error\n", 24);
// 			data->error++;
// 			break ;
// 		}
// 	}
// }

void	cotes_syntax_errors(char *cmd, t_data *data)
{
	int	i;
	int	cotes;
	int dcotes;

	i = 0;
	cotes = 0;
	dcotes = 0;
	data->error = 0;
	while (cmd[i])
	{
		while (cmd[i] && cmd[i] != 39 && cmd[i] != 34)     //(') && ("")
			i++;
		if (cmd[i] == 34)      //(");
		{
			i++;
			while (cmd[i] != 34)    // != (");
				i++;
		}
		if(cmd[i] == 34)       //(");
			i++;
		while (cmd[i] == 39)     // (')
		{
			cotes++;
			i++;
			printf("%d\n", cotes);
		}
		if (cmd[i] == '\0' && (cotes % 2 == 1) && !data->error)
		{
			write(2, "minishell: syntax error\n", 24);
			data->error++;
			break ;
		}
	}
}

int	main(void)
{
	char	*cmd;
	t_data	*data;

	// char	**token;
	data = malloc(sizeof(t_data));
	data->error = 0;
	while (1)
	{
		cmd = readline("minishell-3.2$ ");
		if (!cmd)
		{
			printf("exit\n");
			exit(EXIT_FAILURE);
		}
		add_history(cmd);
		// printf("the cmd is: %s\n", cmd);
		pipe_syntax_errors(cmd, data);
		red_syntax_errors(cmd, data);
		// dcotes_syntax_errors(cmd, data);
		cotes_syntax_errors(cmd, data);
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

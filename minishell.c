/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:53:19 by mhassani          #+#    #+#             */
/*   Updated: 2023/05/25 22:33:37 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	int		i;
	char	*cmd;
	t_data	*data;
	char	**token;
	int		j;

	// char	**token;
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
		token = ft_split(cmd, '|');
		j = 0;
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
		j = 0;
		while (token[j])
		{
			printf("token[%d] = %s\n", j, token[j]);
			j++;
		}
		j = 0;
		while (token[j])
		{
			free(token[j]);
			j++;
		}
		free(token);
		// Free the memory allocated by readline
		free(cmd);
	}
	return (0);
}

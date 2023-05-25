/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:53:19 by mhassani          #+#    #+#             */
/*   Updated: 2023/05/25 13:09:46 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	int		i;
	int j = 0;
	char	*cmd;
	t_data	*data;
	char	**token;

	i = 0;
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
		// printf("the cmd is: %s\n", cmd);
		data->error = 0;
		syntax_errors(cmd, data);
		token = ft_split(cmd, '|');
		i = 0;
		while (token[i])
		{
			//printf("token [%d]: %s\n", i, token[i]);
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

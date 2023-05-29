/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:53:19 by mhassani          #+#    #+#             */
/*   Updated: 2023/05/29 15:36:43 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*cmd;
	char	*command;
	t_data	*data;
	t_token	*t;
	char	**tokens;
	char	**words;
	int		i;
	int		j;

	data = malloc(sizeof(t_data));
	t = malloc(sizeof(t_token));
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
		if (data->error == 0)
		{
			// replace_red_in_quotes(cmd);
			// printf("before cmd: %s\n", cmd);
			command = ft_strdup(cmd); //add space before and after (< / >);
			// bring_back(command);
			// printf("after  cmd: %s\n", command);
			replace_pipe_in_quotes(command);
			tokens = split_with_pipe(command);
			j = 0;
			while (tokens[j])
			{
				printf("===>token[%d]: %s\n", j, tokens[j]);
				replace_space_in_quotes(tokens[j]);
				words = split_with_space(tokens[j]);
				i = 0;
				while (words[i])
				{
					printf("words[%d]: %s\n", i, words[i]);
					i++;
				}
				j++;
			}
			free(cmd);
			free(command);
		}
	}
	return (0);
}

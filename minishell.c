/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:53:19 by mhassani          #+#    #+#             */
/*   Updated: 2023/06/01 19:05:58 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*cmd;
	char	*command;
	char	**tokens;
	char	**words;
	t_data	*data;
	t_token	*t;
	t_token	*ptr;
	t_token *clone;
	int		i;
	int		j;
	int		k;
	int		c;

	t = NULL;
	c = 0;
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
		data->flag = 0;
		syntax_errors(cmd, data);
		if (data->error == 0)
		{
			command = ft_strdup(cmd); //add space before and after (< / >);
			replace_pipe_in_quotes(command);
			tokens = split_with_pipe(command);
			j = 0;
			t = malloc(sizeof(t_token));
			clone = t;
			while (tokens[j])
			{
				printf("===>token[%d]: %s\n", j, tokens[j]);
				replace_space_in_quotes(tokens[j]);
				words = split_with_space(tokens[j]);
				k = 0;
				i = 0;
				t->next = NULL;
				t->arg = malloc((sizeof(char *)) * 100);
				while (words[i])
				{
					t->red = malloc(sizeof(t_redirection) * 100);
					// printf("words[%d]: %s\n", i, words[i]); //hello
					if (words[i][0] == '>' && words[i][1] == '>')
					{
						t->red->redirection = 2;
						t->red->file = ft_strdup(words[i + 1]);
						// printf("append: %s\n", t->red->file);
						data->flag++;
					}
					else if (words[i][0] == '<' && words[i][1] == '<')
					{
						t->red->redirection = 3;
						t->red->limiter = ft_strdup(words[i + 1]);
						// printf("limiter: %s\n", t->red->limiter);
						data->flag++;
					}
					else if (words[i][0] == '<')
					{
						t->red->redirection = 0;
						t->red->file = ft_strdup(words[i + 1]);
						// printf("infile: %s\n", t->red->file);
						data->flag++;
					}
					else if (words[i][0] == '>')
					{
						t->red->redirection = 1;
						t->red->file = ft_strdup(words[i + 1]);
						// printf("outfile: %s\n", t->red->file);
						data->flag++;
					}
					else
					{
						if (i == 0)
						{
							// printf("here\n");
							t->cmd = malloc(sizeof(char) * 100);
							t->cmd = ft_strdup(words[i]);
							// printf("t->cmd: %s\n", t->cmd);
						}
						else if (i != 0 && !data->flag)
						{
							t->arg[k] = malloc(sizeof(char) * 100);
							t->arg[k] = ft_strdup(words[i]);
							// printf("t->arg[%d]: %s\n", k, t->arg[k]);
							k++;
						}
					}
					i++;
				}
				data->flag = 0;
				ptr = malloc(sizeof(t_token)); //creat new node;
				t->next = ptr; // Set t->next point to the new node
				t = t->next;
				j++;
			}
		}

		i = 0;
		while (clone->next)
		{
			if (clone->cmd)
				printf("cmd ptr: %s\n", clone->cmd);
			while (clone->arg[i])
			{
				printf("arg clone[%d]: %s\n", i, clone->arg[i]);
				i++;
			}
			i = 0;
			// while (clone->red->next)
			// {
			// 	printf("oyoyoyoyo\n");
			// 	printf("red: %s\n", t->red->file);
			// 	clone->red = clone->red->next;
			// }
			clone = clone->next;
		}
	}
	free(cmd);
	free(command);
	free(data);
	free(t);
	return (0);
}

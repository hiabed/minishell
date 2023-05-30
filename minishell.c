/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:53:19 by mhassani          #+#    #+#             */
/*   Updated: 2023/05/30 23:48:52 by mhassani         ###   ########.fr       */
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
	t_token *ptr;
	int		i;
	int		j;
	int		k;

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
		ptr = t;
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
			while (tokens[j])
			{
				t->arg = malloc((sizeof(char *)) * 100);
				printf("===>token[%d]: %s\n", j, tokens[j]);
				replace_space_in_quotes(tokens[j]);
				words = split_with_space(tokens[j]);
				
				k = 0;
				i = 0;
				while (words[i])
				{
					t->red = malloc(sizeof(t_redirection) * 100);
					t->red->file = malloc(sizeof(char) * 100);
					// printf("words[%d]: %s\n", i, words[i]); //hello
					if (words[i][0] == '>' && words[i][1] == '>')
					{
						t->red->redirection = 2;
						t->red->file = words[i + 1];
						// printf("append: %s\n", t->red->file);
						data->flag++;
					}
					else if (words[i][0] == '<' && words[i][1] == '<')
					{
						t->red->redirection = 3;
						t->red->limiter = words[i + 1];
						// printf("limiter: %s\n", t->red->limiter);
						data->flag++;
					}
					else if (words[i][0] == '<')
					{
						t->red->redirection = 0;
						t->red->file = words[i + 1];
						// printf("infile: %s\n", t->red->file);
						data->flag++;
					}
					else if (words[i][0] == '>')
					{
						t->red->redirection = 1;
						t->red->file = words[i + 1];
						// printf("outfile: %s\n", t->red->file);
						data->flag++;
					}
					else
					{
						if (i == 0)
						{
							// printf("here\n");
							t->cmd = words[i];
							// printf("t->cmd: %s\n", t->cmd);
						}
						else if (i != 0 && !data->flag)
						{
							// printf("k: %d\n", k);
							t->arg[k] = words[i];
							// printf("k: %d\n", k);
							// printf("t->arg[%d]: %s\n", k, t->arg[k]);
							k++;
						}
					}
					i++;
				}
				t->next = malloc(sizeof(t_token));
				data->flag = 0;
				k = 0;
				t = t->next;
				j++;
			}
			free(cmd);
			free(command);
		}
		t->next = NULL;
		break;
	}
		printf("here\n");
	i = 0;
	while(ptr && ptr->next)
	{
		printf("cmd ptr: %s\n", ptr->cmd);
		printf("arg ptr: %s\n", ptr->arg[i]);
		// printf("file: %s\n", ptr->red->file);
		ptr = ptr->next;
	}
	return (0);
}

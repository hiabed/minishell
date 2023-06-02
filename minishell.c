/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:53:19 by mhassani          #+#    #+#             */
/*   Updated: 2023/06/02 22:49:32 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_redirections(char **words)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (words[i])
	{
		if (words[i][0] == '>' || words[i][0] == '<')
			i = i + 2;
		else if (i == 0)
			i++;
		else
		{
			k++;
			i++;
		}
	}
	return (k);
}

char	**ft_arg(char **words)
{
	char	**args;
	int		i;
	int		k;

	k = count_redirections(words);
	args = malloc(sizeof(char *) * (k + 1));
	i = 0;
	k = 0;
	while (words[i])
	{
		if (words[i][0] == '>' || words[i][0] == '<')
			i = i + 2;
		else if (i == 0)
			i++;
		else
			args[k++] = words[i++];
	}
	args[k] = NULL;
	return (args);
}

char	*ft_cmd(char **words)
{
	if (words[0] && words[0][0] != '>' && words[0][0] != '<')
		return (words[0]);
	return (NULL);
}

void	ft_lstadd_token(t_token **lst, t_token *new)
{
	t_token	*ptr;

	ptr = *lst;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}

t_token	*ft_lstnew_token(char **words)
{
	t_token	*head;
	int		i;

	i = 0;
	head = malloc(sizeof(t_token));
	if (!head)
		return (NULL);
	head->red = ft_redirections(words);
	head->cmd = ft_cmd(words);
	head->arg = ft_arg(words);
	head->next = NULL;
	return (head);
}

int	main(void)
{
	char	*cmd;
	char	*command;
	char	**tokens;
	char	**words;
	t_data	*data;
	t_token	*ptr;
	t_token	*data2;
	int		j;

	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	while (1)
	{
		cmd = readline("minishell-3.2$ ");
		ptr = NULL;
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
			while (tokens[j])
			{
				// printf("===>token[%d]: %s\n", j, tokens[j]);
				replace_space_in_quotes(tokens[j]);
				words = split_with_space(tokens[j]);
				ft_lstadd_token(&ptr, ft_lstnew_token(words));
				j++;
			}
			data2 = ptr;
			while (data2)
			{
				j = 0;
				printf("cmd: %s\n", data2->cmd);
				while (data2->arg[j])
				{
					printf("arg: %s\n", data2->arg[j]);
					j++;
				}
				while (data2->red)
				{
					printf("type: %d\n", data2->red->type);
					printf("limiter: %s\n", data2->red->limiter);
					printf("file: %s\n", data2->red->file);
					data2->red = data2->red->next;
				}
				data2 = data2->next;
			}
		}
	}
	free(cmd);
	free(command);
	free(data);
	return (0);
}

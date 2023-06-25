/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:13:02 by mhassani          #+#    #+#             */
/*   Updated: 2023/06/23 18:45:46 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	empty_string_condition(char *words, int *i)
{
	if ((words[*i] == '\"' && words[*i + 1] == '\"') || (words[*i] == '\''
			&& words[*i + 1] == '\''))
		return (1);
	return (0);
}

int	ft_number_type(char *words)
{
	if (words[0] == '<' && words[1] == '<')
		return (4);
	else if (words[0] == '>' && words[1] == '>')
		return (3);
	else if (words[0] == '<')
		return (2);
	else if (words[0] == '>')
		return (1);
	return (0);
}

void	redirections(t_token *ptr, t_env *envp)
{
	t_token	*redir = ptr;
	t_env 	*temp;

	temp = envp;
	redir->red = ptr->red;
	redir->out = 0;
	redir->fd = 0;
	while (redir->red)
	{
		if (redir->red->type == 4)
			here_doc(redir, temp);
		else if (redir->red->type == 3)
			redir->out = open(redir->red->file, O_CREAT | O_RDWR | O_APPEND, 0644);
		else if (redir->red->type == 1)
			redir->out = open(redir->red->file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		else if (redir->red->type == 2)
			redir->fd = open(redir->red->file, O_RDONLY, 0644);
		redir->red = redir->red->next;
	}
}

void	infos_without_quotes(t_token *ptr, t_env *envp)
{
	int		i;
	t_token	*data;

	data = ptr;
	while (data)
	{
		i = 0;
		if (data->cmd)
			data->cmd = join_strings_to_be_one(data->cmd, envp);
		while (data->arg[i])
		{
			data->arg[i] = join_strings_to_be_one(data->arg[i], envp);
			i++;
		}
		redirections(data, envp);
		data = data->next;
	}
}

void	print_data(t_token *ptr)
{
	int		i;
	t_token	*data;

	data = ptr;
	
	while (data)
	{
		i = 0;
		printf("------------------\n");
		if (data->cmd)
			printf("cmd: %s\n", data->cmd);
		while (data->arg[i])
		{
			printf("arg: %s\n", data->arg[i]);
			i++;
		}
		while (data->red)
		{
			printf("type: %d\n", data->red->type);
			printf("limiter: %s\n", data->red->limiter);
			printf("file: %s\n", data->red->file);
			data->red = data->red->next;
		}
		data = data->next;
	}
}

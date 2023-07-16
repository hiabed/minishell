/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:13:02 by mhassani          #+#    #+#             */
/*   Updated: 2023/07/16 23:40:14 by mhassani         ###   ########.fr       */
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

int	redirections(t_token **ptr, t_env *envp)
{
	t_redirection	*red1 = (*ptr)->red;
	t_redirection 	*red = (*ptr)->red;
	t_env 	*temp;

	temp = envp;
	(*ptr)->out = 1;
	(*ptr)->fd = 0;
	while (red1)
	{
		if (red1->type == 4)
		{
			(*ptr)->fd = here_doc(red1->limiter, temp);
		}
		if ((*ptr)->fd == 1)
			return (1);
		red1 = red1->next;
	}
	while(red)
	{
		if (red->type == 3)
			(*ptr)->out = open(red->file, O_CREAT | O_RDWR | O_APPEND, 0644);
		else if (red->type == 1)
			(*ptr)->out = open(red->file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		else if (red->type == 2)
			(*ptr)->fd = open(red->file, O_RDONLY, 0644);
		red = red->next;
	}
	return (0);
}

void	infos_without_quotes(t_token **ptr, t_env *envp)
{
	int		i;
	char *cmd_tmp;
	t_token	*data;
	t_token *data2 = *ptr;
	int ch = 1;
	data = *ptr;
	while (data2)
	{
		int x = redirections(&data2, envp);
		if(x)
			ch  = 0;
		if (!ch)
			break ;
		data2 = data2->next;
	}
	if (ch)
	{
		while (data)
		{
			i = 0;
			if (data->cmd){
				cmd_tmp = data->cmd;
				data->cmd = join_strings_to_be_one(data->cmd, envp);
				free(cmd_tmp);
			}
			while (data->arg[i])
			{
				cmd_tmp = data->arg[i];
				data->arg[i] = join_strings_to_be_one(data->arg[i], envp);
				free(cmd_tmp);
				i++;
			}
			data = data->next;
		}
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

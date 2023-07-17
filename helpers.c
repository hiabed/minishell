/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:13:02 by mhassani          #+#    #+#             */
/*   Updated: 2023/07/17 23:58:14 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_files(t_redirection *red, t_token **ptr)
{
	while(red)
	{
		if (red->type == 3)
		{
			(*ptr)->out = open(red->file, O_CREAT | O_RDWR | O_APPEND, 0644);
			if((*ptr)->out == -1)
				ft_Error((*ptr)->red->file, 5);
		}
		else if (red->type == 1)
		{
			(*ptr)->out = open(red->file, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if((*ptr)->out == -1)
				ft_Error((*ptr)->red->file, 5);
		}
		else if (red->type == 2)
		{
			(*ptr)->fd = open(red->file, O_RDONLY, 0644);
			if((*ptr)->fd == -1)
				ft_Error((*ptr)->red->file, 5);
			else if (access((*ptr)->red->file, R_OK))
				write(2, "permission denied\n", 18);	
		}
		red = red->next;
	}
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
			(*ptr)->fd = here_doc(red1->limiter, temp);
		if ((*ptr)->fd == 1)
			return (1);
		red1 = red1->next;
	}
	open_files(red, ptr);
	return (0);
}

void	commands(t_token *data, int signal_check, t_env *envp)
{
	char *cmd_tmp;
	int i = 0;
	if (!signal_check)
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

void	infos_without_quotes(t_token **ptr, t_env *envp)
{
	t_token	*data;
	t_token *data2 = *ptr;
	int signal_check = 0;
	data =    *ptr;
	while (data2)
	{
		if(redirections(&data2, envp))
			signal_check = 1;
		if (signal_check)
			break ;
		data2 = data2->next;
	}
	commands(data, signal_check, envp);
}

// void	print_data(t_token *ptr)
// {
// 	int		i;
// 	t_token	*data;

// 	data = ptr;
// 	while (data)
// 	{
// 		i = 0;
// 		printf("------------------\n");
// 		if (data->cmd)
// 			printf("cmd: %s\n", data->cmd);
// 		while (data->arg[i])
// 		{
// 			printf("arg: %s\n", data->arg[i]);
// 			i++;
// 		}
// 		while (data->red)
// 		{
// 			printf("type: %d\n", data->red->type);
// 			printf("limiter: %s\n", data->red->limiter);
// 			printf("file: %s\n", data->red->file);
// 			data->red = data->red->next;
// 		}
// 		data = data->next;
// 	}
// }

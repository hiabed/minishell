/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:13:02 by mhassani          #+#    #+#             */
/*   Updated: 2023/07/14 22:53:48 by mhassani         ###   ########.fr       */
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
	t_token	*data = ptr;
	t_redirection *red = ptr->red;
	t_env 	*temp;
	int status;

	temp = envp;
	data->out = 1;
	data->fd = 0;
	signal(SIGINT, SIG_IGN);
	int id = fork();
	if(id == 0)
	{
		while (data->red)
		{
			if (red->type == 4)
				data->fd = here_doc(data, temp);
			data->red = data->red->next;
		}
		// g_g.signal_check = 1;
		exit(0);
	}
	else
		waitpid(id, &status, 0);
	// if (WEXITSTATUS(status) == 1)
	// {
	// 	g_g.signal_check = WEXITSTATUS(status);
	// 	g_g.exit_status = WEXITSTATUS(status);
	// }
	while(data->red)
	{
		if (red->type == 3)
			data->out = open(red->file, O_CREAT | O_RDWR | O_APPEND, 0644);
		else if (red->type == 1)
			data->out = open(red->file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		else if (red->type == 2)
			data->fd = open(red->file, O_RDONLY, 0644);
		data->red = data->red->next;
	}
}

void	infos_without_quotes(t_token *ptr, t_env *envp)
{
	int		i;
	char *cmd_tmp;
	t_token	*data;

	data = ptr;
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

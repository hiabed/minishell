/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 21:30:24 by mhassani          #+#    #+#             */
/*   Updated: 2023/05/26 15:12:57 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_syntax_errors(char *cmd, t_data *data)
{
	int	i;
    int pipe;

	i = 0;
    pipe = 0;
	while (cmd[i] == ' ' || cmd[i] == '\t')
		i++;
	if (cmd[i] == '|' && !data->error)
	{
		write(2, "minishell: syntax error\n", 24);
		data->error++;
	}
	while (cmd[i])
	{
        if (cmd[i] == 34 || cmd[i] == 39) //(");
		{
			i++;
			while (cmd[i] && (cmd[i] != 34 || cmd[i] == 39)) // != (");
				i++;
			if (cmd[i] == 34 || cmd[i] == 39) // == (");
                i++;
		}
		if (cmd[i] == '|')
		{
			i++;
			while (cmd[i] == ' ' || cmd[i] == '\t')
				i++;
			if ((cmd[i] == '\0' || cmd[i] == '|') && !data->error)
			{
				write(2, "minishell: syntax error\n", 24);
				data->error++;
			}
		}
		i++;
	}
}

void	red_syntax_errors(char *cmd, t_data *data)
{
	int	i;

	i = 0;
	while (cmd[i] == ' ' || cmd[i] == '\t')
		i++;
	while (cmd[i])
	{
        if (cmd[i] == 34 || cmd[i] == 39) //(");
		{
			i++;
			while (cmd[i] && (cmd[i] != 34 || cmd[i] == 39)) // != (");
				i++;
			if (cmd[i] == 34 || cmd[i] == 39) // == (");
                i++;
		}
		if (cmd[i] == '>')
		{
			i++;
			if(cmd[i] == '>')
				i++;
			if(cmd[i] == '>' && !data->error)
			{
				write(2, "minishell: syntax error\n", 24);
				data->error++;
			}
			while (cmd[i] == ' ' || cmd[i] == '\t')
				i++;
			if ((cmd[i] == '\0' || cmd[i] == '>' || cmd[i] == '<'
					|| cmd[i] == '|') && !data->error)
			{
				write(2, "minishell: syntax error\n", 24);
				data->error++;
			}
		}
		if (cmd[i] == '<')
		{
			i++;
			if(cmd[i] == '<')
				i++;
			if(cmd[i] == '<' && !data->error)
			{
				write(2, "minishell: syntax error\n", 24);
				data->error++;
			}
			while (cmd[i] == ' ' || cmd[i] == '\t')
				i++;
			if ((cmd[i] == '\0' || cmd[i] == '>' || cmd[i] == '<'
					|| cmd[i] == '|') && !data->error)
			{
				write(2, "minishell: syntax error\n", 24);
				data->error++;
			}
		}
		i++;
	}
}

void	cotes_syntax_errors(char *cmd, t_data *data)
{
	int	i;
	int	cotes;
	int	dcotes;
    int in_out;

	i = 0;
	cotes = 0;
	dcotes = 0;
    in_out = 0;
	while (cmd[i])
	{
		while (cmd[i] && cmd[i] != 39 && cmd[i] != 34) //(') && ("")
			i++;
		if (cmd[i] == 34) //(");
		{
			dcotes++;
			i++;
			while (cmd[i] && cmd[i] != 34) // != (");
			{
				if (cmd[i] == 39)
					cotes++;
				i++;
			}
			if (cmd[i] == 34) // == (");
			{
				dcotes = 0;
				cotes = 0;
				i++;
			}
		}
		if (cmd[i] == 39) //(');
		{
			cotes++;
			i++;
			while (cmd[i] && cmd[i] != 39) // != (');
			{
				if (cmd[i] == 34) // (");
					dcotes++;
				i++;
			}
			if (cmd[i] == 39) // == (');
			{
				cotes = 0;
				dcotes = 0;
				i++;
			}
		}
		if (!cmd[i] && (cotes % 2 == 1 || dcotes % 2 == 1) && !data->error)
		{
			write(2, "minishell: syntax error\n", 24);
			data->error++;
		}
	}
}

void	syntax_errors(char *cmd, t_data *data)
{
	cotes_syntax_errors(cmd, data);
	pipe_syntax_errors(cmd, data);
	red_syntax_errors(cmd, data);
}
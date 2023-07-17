/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 21:30:24 by mhassani          #+#    #+#             */
/*   Updated: 2023/07/17 13:31:05 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_syntax_errors(char *cmd, t_data *data)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\"')
			skip_db_quotes(&i, cmd);
		else if (cmd[i] == '\'')
			skip_sin_quotes(&i, cmd);
		else if (cmd[i] == '|')
		{
			i++;
			while (cmd[i] == ' ' || cmd[i] == '\t')
				i++;
			if ((cmd[i] == '\0' || cmd[i] == '|') && !data->error)
			{
				write(2, "minishell: syntax error\n", 24);
				write(2, "Pipe2\n", 6);
				data->error++;
			}
		}
		else
			i++;
	}
}

void	infile_errors(char *cmd, int *i, t_data *data)
{
	(*i)++;
	if (cmd[*i] == '<')
		(*i)++;
	if (cmd[*i] == '<' && !data->error)
	{
		write(2, "minishell: syntax error\n", 24);
		write(2, "red\n", 4);
		data->error++;
	}
	while (cmd[*i] == ' ' || cmd[*i] == '\t')
		(*i)++;
	if ((cmd[*i] == '\0' || cmd[*i] == '>' || cmd[*i] == '<' || cmd[*i] == '|')
		&& !data->error)
	{
		write(2, "minishell: syntax error\n", 24);
		write(2, "red\n", 4);
		data->error++;
	}
}

void	red_syntax_errors(char *cmd, t_data *data)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\"')
			skip_db_quotes(&i, cmd);
		else if (cmd[i] == '\'')
			skip_sin_quotes(&i, cmd);
		else if (cmd[i] == '>')
			outfile_errors(cmd, &i, data);
		else if (cmd[i] == '<')
			infile_errors(cmd, &i, data);
		else
			i++;
	}
}

void	cotes_syntax_errors(char *cmd, t_data *data)
{
	int	i;
	int	cotes;
	int	dcotes;

	i = 0;
	cotes = 0;
	dcotes = 0;
	while (cmd[i])
	{
		while (cmd[i] && cmd[i] != '\'' && cmd[i] != '\"')
			i++;
		if (cmd[i] && cmd[i] == '\"')
			d_quotes_errors(&dcotes, &cotes, &i, cmd);
		if (cmd[i] && cmd[i] == '\'')
			s_quotes_errors(&dcotes, &cotes, &i, cmd);
		if (!cmd[i] && (cotes % 2 == 1 || dcotes % 2 == 1) && !data->error)
		{
			write(2, "minishell: syntax error\n", 24);
			write(2, "quotes\n", 7);
			data->error++;
		}
	}
}

void	syntax_errors(char *cmd, t_data *data)
{
	cotes_syntax_errors(cmd, data);
	pipe_syntax_errors(cmd, data);
	red_syntax_errors(cmd, data);
	herdocs_count(cmd, data);
}

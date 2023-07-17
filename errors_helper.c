/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 21:32:29 by mhassani          #+#    #+#             */
/*   Updated: 2023/07/17 19:11:24 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_db_quotes(int *i, char *cmd)
{
	(*i)++;
	while (cmd[*i] && cmd[*i] != '\"')
		(*i)++;
	if (cmd[*i] == '\"')
		(*i)++;
}

void	skip_sin_quotes(int *i, char *cmd)
{
	(*i)++;
	while (cmd[*i] && cmd[*i] != '\'')
		(*i)++;
	if (cmd[*i] == '\'')
		(*i)++;
}

void	outfile_errors(char *cmd, int *i, t_data *data)
{
	(*i)++;
	if (cmd[*i] == '>')
		(*i)++;
	if (cmd[*i] == '>' && !data->error)
	{
		write(2, "minishell: syntax error near unexpected token `>'\n", 50);
		g_g.exit_status = 258;
		data->error++;
	}
	while (cmd[*i] && (cmd[*i] == ' ' || cmd[*i] == '\t'))
		(*i)++;
	if ((cmd[*i] == '\0' || cmd[*i] == '>' || cmd[*i] == '<' || cmd[*i] == '|')
		&& !data->error)
	{
		write(2, "minishell: syntax error near unexpected token `newline'\n", 56);
		g_g.exit_status = 258;
		data->error++;
	}
}

void	d_quotes_errors(int *dcotes, int *cotes, int *i, char *cmd)
{
	(*dcotes)++;
	(*i)++;
	while (cmd[*i] && cmd[*i] != '\"')
	{
		if (cmd[*i] && cmd[*i] == '\'')
			(*cotes)++;
		(*i)++;
	}
	if (cmd[*i] && cmd[*i] == '\"')
	{
		*dcotes = 0;
		*cotes = 0;
		(*i)++;
	}
}

void	s_quotes_errors(int *dcotes, int *cotes, int *i, char *cmd)
{
	(*cotes)++;
	(*i)++;
	while (cmd[*i] && cmd[*i] != '\'')
	{
		if (cmd[*i] == '\"')
			(*dcotes)++;
		(*i)++;
	}
	if (cmd[*i] && cmd[*i] == '\'')
	{
		*cotes = 0;
		*dcotes = 0;
		(*i)++;
	}
}

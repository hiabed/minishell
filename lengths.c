/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lengths.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 20:31:36 by mhassani          #+#    #+#             */
/*   Updated: 2023/07/18 23:42:42 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_strings(char *words)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (words[i])
	{
		if (words[i + 1] && ((words[i] == '\"' && words[i + 1] == '\"')
				|| (words[i] == '\'' && words[i + 1] == '\'')))
		{
			i = i + 2;
			count++;
		}
		else if (words[i] == '\"' && words[i + 1] != '\"')
			skip_d_quotes(words, &i, &count);
		else if (words[i] == '\'' && words[i + 1] != '\'')
			skip_s_quotes(words, &i, &count);
		else if (words[i] != '\"' && words[i] != '\'')
		{
			while (words[i] && (words[i] != '\"' && words[i] != '\''))
				i++;
			count++;
		}
	}
	return (count);
}

int	word_len(char *words)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (words[i] && words[i] != '\"')
	{
		count++;
		i++;
	}
	return (count);
}

int	word_len_single(char *words)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (words[i] && words[i] != '\'')
	{
		count++;
		i++;
	}
	return (count);
}

int	len(char *words)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (words[i] && words[i] != '\'' && words[i] != '\"')
	{
		count++;
		i++;
	}
	return (count);
}

void	herdocs_count(char *cmd, t_data *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (cmd[i + 1] && cmd[i] == '<' && cmd[i + 1] == '<')
			count++;
		i++;
	}
	if (count > 16 && !data->error)
	{
		write(2, "minishell-3.2: maximum here-document count exceeded\n", 52);
		g_g.exit_status = 2;
		exit(g_g.exit_status);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 23:32:42 by mhassani          #+#    #+#             */
/*   Updated: 2023/06/22 23:18:12 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc(t_token *p, t_env *envp)
{
	char	*line;
	int		i;
	int		pipefd[2];
	envp = NULL;

	i = 0;
	pipe(pipefd);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("exit\n");
			exit(EXIT_FAILURE);
		}
		if (!(ft_strcmp(p->red->limiter, line)))
			break ;
		ft_putendl_fd(line, pipefd[1]);
		//close(pipefd[0]);
		free(line);
	}
	g_g.pipefd = pipefd[0];
	free(line);
	close(pipefd[1]);
	return (pipefd[0]);
}

char	**heredoc_without_quotes(char *words)
{
	int	i;

	g_g.str = malloc((count_strings(words) + 1) * sizeof(char *));
	g_g.k = 0;
	i = 0;
	while (words[i])
	{
		if (empty_string_condition(words, &i))
			g_g.str[g_g.k] = empty_string(g_g.str[g_g.k], &i);
		else if ((words[i] == '\"' && words[i + 1] != '\"'))
			g_g.str[g_g.k] = fill_word_with_d_q(g_g.str[g_g.k], words, &i);
		else if ((words[i] == '\'' && words[i + 1] != '\''))
			g_g.str[g_g.k] = fill_word_with_s_q(g_g.str[g_g.k], words, &i);
		else if (words[i] != '\"' && words[i] != '\'')
			g_g.str[g_g.k] = fill_word_without_q(g_g.str[g_g.k], words, &i);
		g_g.k++;
	}
	g_g.str[g_g.k] = NULL;
	return (g_g.str);
}

void	skip_d_quotes(char *words, int *i, int *count)
{
	(*i)++;
	while (words[*i] && words[*i] != '\"')
		(*i)++;
	if (words[*i])
		(*i)++;
	(*count)++;
}

void	skip_s_quotes(char *words, int *i, int *count)
{
	(*i)++;
	while (words[*i] && words[*i] != '\'')
		(*i)++;
	if (words[*i])
		(*i)++;
	(*count)++;
}

void	increment_i(char *cmd, int *i)
{
	(*i)++;
	while (cmd[*i] && cmd[*i] != '\"')
		(*i)++;
	if (cmd[*i] && cmd[*i + 1] && cmd[*i] == '\"')
		(*i)++;
}

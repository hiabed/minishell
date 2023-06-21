/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:53:19 by mhassani          #+#    #+#             */
/*   Updated: 2023/06/21 21:56:02 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**strings_without_quotes(char *words, char **envp)
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
		{
			g_g.str[g_g.k] = fill_word_with_d_q(g_g.str[g_g.k], words, &i);
			g_g.str[g_g.k] = fill_expand(g_g.str[g_g.k], envp);
		}
		else if ((words[i] == '\'' && words[i + 1] != '\''))
			g_g.str[g_g.k] = fill_word_with_s_q(g_g.str[g_g.k], words, &i);
		else if (words[i] != '\"' && words[i] != '\'')
		{
			g_g.str[g_g.k] = fill_word_without_q(g_g.str[g_g.k], words, &i);
			g_g.str[g_g.k] = fill_expand(g_g.str[g_g.k], envp);
		}
		g_g.k++;
	}
	g_g.str[g_g.k] = NULL;
	return (g_g.str);
}

char	*join_strings_to_be_one(char *words, char **envp)
{
	int		i;
	char	*joined_string;
	char	**to_be_joined;
	char	*temp;

	i = 0;
	joined_string = words;
	to_be_joined = strings_without_quotes(words, envp);
	if (to_be_joined[i])
	{
		joined_string = to_be_joined[i];
		while (to_be_joined[i + 1])
		{
			temp = ft_strjoin(joined_string, to_be_joined[i + 1]);
			joined_string = temp;
			i++;
		}
	}
	return (joined_string);
}

char	*join_heredoc_to_be_one(char *words)
{
	int		i;
	char	*joined_string;
	char	**to_be_joined;
	char	*temp;

	i = 0;
	joined_string = words;
	to_be_joined = heredoc_without_quotes(words);
	if (to_be_joined[i])
	{
		joined_string = to_be_joined[i];
		while (to_be_joined[i + 1])
		{
			temp = ft_strjoin(joined_string, to_be_joined[i + 1]);
			joined_string = temp;
			i++;
		}
	}
	return (joined_string);
}

void	minishell(t_data *data, char *cmd, char **envp)
{
	int	i;

	data->error = 0;
	data->flag = 0;
	syntax_errors(cmd, data);
	if (!data->error)
	{
		g_g.command = space_arround_red(cmd);
		replace_pipe_in_quotes(g_g.command);
		g_g.tokens = split_with_pipe(g_g.command);
		i = 0;
		g_g.ptr = NULL;
		while (g_g.tokens[i])
		{
			replace_space_in_quotes(g_g.tokens[i]);
			g_g.words = split_with_space(g_g.tokens[i]);
			ft_lstadd_token(&g_g.ptr, ft_lstnew_token(g_g.words, envp));
			i++;
		}
		infos_without_quotes(g_g.ptr, envp);
		print_data(g_g.ptr);
	}
}

int	main(int ac, char **av, char **envp)
{
	ac = 0;
	av = NULL;
	g_g.data = malloc(sizeof(t_data));
	if (!g_g.data)
		return (0);
	g_g.exit_status = 1;
	while (1)
	{
		g_g.cmd = readline("minishell-3.2$ ");
		if (!g_g.cmd)
		{
			printf("exit\n");
			exit(EXIT_FAILURE);
		}
		add_history(g_g.cmd);
		minishell(g_g.data, g_g.cmd, envp);
	}
	free(g_g.cmd);
	free(g_g.command);
	system("leaks minishell");
	return (0);
}

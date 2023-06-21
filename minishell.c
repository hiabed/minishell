/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:53:19 by mhassani          #+#    #+#             */
/*   Updated: 2023/06/21 18:51:55 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**strings_without_quotes(char *words, char **envp)
{
	int	i;

	g.str = malloc((count_strings(words) + 1) * sizeof(char *));
	g.k = 0;
	i = 0;
	while (words[i])
	{
		if (empty_string_condition(words, &i))
			g.str[g.k] = empty_string(g.str[g.k], &i);
		else if ((words[i] == '\"' && words[i + 1] != '\"'))
		{
			g.str[g.k] = fill_word_with_d_quotes(g.str[g.k], words, &i);
			g.str[g.k] = fill_expand(g.str[g.k], envp);
		}
		else if ((words[i] == '\'' && words[i + 1] != '\''))
			g.str[g.k] = fill_word_with_s_quotes(g.str[g.k], words, &i);
		else if (words[i] != '\"' && words[i] != '\'')
		{
			g.str[g.k] = fill_word_without_quotes(g.str[g.k], words, &i);
			g.str[g.k] = fill_expand(g.str[g.k], envp);
		}
		g.k++;
	}
	g.str[g.k] = NULL;
	return (g.str);
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

char	**heredoc_without_quotes(char *words)
{
	int	i;

	g.str = malloc((count_strings(words) + 1) * sizeof(char *));
	g.k = 0;
	i = 0;
	while (words[i])
	{
		if (empty_string_condition(words, &i))
			g.str[g.k] = empty_string(g.str[g.k], &i);
		else if ((words[i] == '\"' && words[i + 1] != '\"'))
			g.str[g.k] = fill_word_with_d_quotes(g.str[g.k], words, &i);
		else if ((words[i] == '\'' && words[i + 1] != '\''))
			g.str[g.k] = fill_word_with_s_quotes(g.str[g.k], words, &i);
		else if (words[i] != '\"' && words[i] != '\'')
			g.str[g.k] = fill_word_without_quotes(g.str[g.k], words, &i);
		g.k++;
	}
	g.str[g.k] = NULL;
	return (g.str);
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

int	main(int ac, char **av, char **envp)
{
	int	i;

	ac = 0;
	av = NULL;
	g.data = malloc(sizeof(t_data));
	if (!g.data)
		return (0);
	g.exit_status = 1;
	while (1)
	{
		g.cmd = readline("minishell-3.2$ ");
		if (!g.cmd)
		{
			printf("exit\n");
			exit(EXIT_FAILURE);
		}
		add_history(g.cmd);
		g.data->error = 0;
		g.data->flag = 0;
		syntax_errors(g.cmd, g.data);
		if (!g.data->error)
		{
			g.command = space_arround_red(g.cmd);
			replace_pipe_in_quotes(g.command);
			g.tokens = split_with_pipe(g.command);
			i = 0;
			g.ptr = NULL;
			while (g.tokens[i])
			{
				replace_space_in_quotes(g.tokens[i]);
				g.words = split_with_space(g.tokens[i]);
				ft_lstadd_token(&g.ptr, ft_lstnew_token(g.words, envp));
				i++;
			}
			infos_without_quotes(g.ptr, envp);
			print_data(g.ptr);
		}
	}
	free(g.cmd);
	free(g.command);
	system("leaks minishell");
	return (0);
}

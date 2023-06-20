/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:53:19 by mhassani          #+#    #+#             */
/*   Updated: 2023/06/20 18:21:55 by mhassani         ###   ########.fr       */
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
	char	*cmd;
	char	*command;
	char	**tokens;
	char	**words;
	t_data	*data;
	t_token	*ptr;
	int		i;

	ac = 0;
	av = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	g.exit_status = 1;
	while (1)
	{
		cmd = readline("minishell-3.2$ ");
		if (!cmd)
		{
			printf("exit\n");
			exit(EXIT_FAILURE);
		}
		add_history(cmd);
		data->error = 0;
		data->flag = 0;
		syntax_errors(cmd, data);
		if (!data->error)
		{
			command = space_arround_red(cmd);
			replace_pipe_in_quotes(command);
			tokens = split_with_pipe(command);
			i = 0;
			ptr = NULL;
			while (tokens[i])
			{
				replace_space_in_quotes(tokens[i]);
				words = split_with_space(tokens[i]);
				ft_lstadd_token(&ptr, ft_lstnew_token(words, envp));
				i++;
			}
			infos_without_quotes(ptr, envp);
			print_data(ptr);
		}
	}
	free(cmd);
	free(command);
	system("leaks minishell");
	return (0);
}

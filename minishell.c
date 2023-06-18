/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:53:19 by mhassani          #+#    #+#             */
/*   Updated: 2023/06/18 23:32:12 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fill_expand(char *str, char **envp)
{
	int		i;
	int		j;
	int		size;
	char	*expand;

	if (ft_expand_value(str, envp))
	{
		i = 0;
		j = 0;
		size = (ft_strlen(ft_expand_value(str, envp)) + 1);
		expand = ft_expand_value(str, envp);
		str = malloc(size + 1);
		while (expand[j])
			str[i++] = expand[j++];
		str[i] = '\0';
	}
	return (str);
}

char	*fill_word_without_quotes(char *str, char *words, int *i)
{
	int	j;

	j = 0;
	str = malloc(len(&words[*i]) + 1);
	while (words[*i] && words[*i] != '\"' && words[*i] != '\'')
		str[j++] = words[(*i)++];
	str[j] = '\0';
	return (str);
}

char	*fill_word_with_d_quotes(char *str, char *words, int *i)
{
	int	j;

	j = 0;
	(*i)++;
	str = malloc(word_len(&words[*i]) + 1);
	while (words[*i] && words[*i] != '\"')
		str[j++] = words[(*i)++];
	str[j] = '\0';
	if (words[*i])
		(*i)++;
	return (str);
}

char	*fill_word_with_s_quotes(char *str, char *words, int *i)
{
	int	j;

	j = 0;
	(*i)++;
	str = malloc(word_len(&words[*i]) + 1);
	while (words[*i] && words[*i] != '\'')
		str[j++] = words[(*i)++];
	str[j] = '\0';
	if (words[*i])
		(*i)++;
	return (str);
}

char	*empty_string(char *str, int *i)
{
	str = malloc(1);
	str[0] = '\0';
	*i = *i + 2;
	return (str);
}

int	empty_string_condition(char *words, int *i)
{
	if ((words[*i] == '\"' && words[*i + 1] == '\"') || (words[*i] == '\''
			&& words[*i + 1] == '\''))
		return (1);
	return (0);
}

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

// if(!ft_strncmp(no_quotes_str[k], "$_", 2)
// && ft_strlen(no_quotes_str[k]) >= 3)
// {
// 	write(2, "minishell-3.2$ ", 15);
// 	write(2, no_quotes_str[k], ft_strlen(no_quotes_str[k]));
// 	write(2, ": ambiguous redirect\n", 21);
// }

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

void	print_info(t_token *ptr, char **envp)
{
	int		i;
	t_token	*data;

	data = ptr;
	while (data)
	{
		i = 0;
		printf("------------\n");
		if (data->cmd)
		{
			data->cmd = join_strings_to_be_one(data->cmd, envp);
			printf("cmd: %s\n", data->cmd);
		}
		while (data->arg[i])
		{
			data->arg[i] = join_strings_to_be_one(data->arg[i], envp);
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
			print_info(ptr, envp);
		}
	}
	free(cmd);
	free(command);
	system("leaks minishell");
	return (0);
}

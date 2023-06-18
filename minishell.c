/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:53:19 by mhassani          #+#    #+#             */
/*   Updated: 2023/06/18 17:35:44 by mhassani         ###   ########.fr       */
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
		{
			i++;
			while (words[i] && words[i] != '\"')
				i++;
			if (words[i])
				i++;
			count++;
		}
		else if (words[i] == '\'' && words[i + 1] != '\'')
		{
			i++;
			while (words[i] && words[i] != '\'')
				i++;
			if (words[i])
				i++;
			count++;
		}
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

char	**heredoc_without_quotes(char *words)
{
	int		i;
	int		j;
	int		k;
	char	**no_quotes_str;
	char	*expand;

	expand = NULL;
	no_quotes_str = malloc((count_strings(words) + 1) * sizeof(char *));
	k = 0;
	i = 0;
	while (words[i])
	{
		if ((words[i] == '\"' && words[i + 1] == '\"') || (words[i] == '\''
				&& words[i + 1] == '\''))
		{
			no_quotes_str[k] = malloc(1);
			no_quotes_str[k][0] = '\0';
			k++;
			i = i + 2;
		}
		else if ((words[i] == '\"' && words[i + 1] != '\"'))
		{
			j = 0;
			i++;
			no_quotes_str[k] = malloc(word_len(&words[i]) + 1);
			while (words[i] && words[i] != '\"')
				no_quotes_str[k][j++] = words[i++];
			no_quotes_str[k][j] = '\0';
			k++;
			if (words[i])
				i++;
		}
		else if ((words[i] == '\'' && words[i + 1] != '\''))
		{
			j = 0;
			i++;
			no_quotes_str[k] = malloc(word_len_single(&words[i]) + 1);
			while (words[i] && words[i] != '\'')
				no_quotes_str[k][j++] = words[i++];
			no_quotes_str[k][j] = '\0';
			k++;
			if (words[i])
				i++;
		}
		else if (words[i] != '\"' && words[i] != '\'')
		{
			j = 0;
			no_quotes_str[k] = malloc(len(&words[i]) + 1);
			while (words[i] && words[i] != '\"' && words[i] != '\'')
				no_quotes_str[k][j++] = words[i++];
			no_quotes_str[k][j] = '\0';
			k++;
		}
	}
	no_quotes_str[k] = NULL;
	return (no_quotes_str);
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

char	*fill_expand(char *no_quotes_str, char **envp)
{
	int		i;
	int		j;
	int		size;
	char	*expand;

	if (ft_expand_value(no_quotes_str, envp))
	{
		i = 0;
		j = 0;
		size = (ft_strlen(ft_expand_value(no_quotes_str, envp)) + 1);
		expand = ft_expand_value(no_quotes_str, envp);
		no_quotes_str = malloc(size + 1);
		while (expand[j])
			no_quotes_str[i++] = expand[j++];
		no_quotes_str[i] = '\0';
	}
	return (no_quotes_str);
}

char	*fill_word_without_quotes(char *no_quotes_str, char *words)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	no_quotes_str = malloc(len(words) + 1);
	while (words[i] && words[i] != '\"' && words[i] != '\'')
		no_quotes_str[j++] = words[i++];
	no_quotes_str[j] = '\0';
	// no_quotes_str = fill_expand(no_quotes_str, envp);
	return (no_quotes_str);
}

char	*fill_word_with_d_quotes(char *no_quotes_str, char *words)
{
	int	j;
	int	i;

	j = 0;
	i = 1;
	
	no_quotes_str = malloc(word_len(&words[i]) + 1);
	while (words[i] && words[i] != '\"')
		no_quotes_str[j++] = words[i++];
	no_quotes_str[j] = '\0';
	return no_quotes_str;
}

char	*fill_word_with_s_quotes(char *no_quotes_str, char *words)
{
	int	j;
	int	i;

	j = 0;
	i = 1;
	
	no_quotes_str = malloc(word_len(&words[i]) + 1);
	while (words[i] && words[i] != '\'')
		no_quotes_str[j++] = words[i++];
	no_quotes_str[j] = '\0';
	return no_quotes_str;
}

char	*empty_string(char *no_quotes_str)
{
	no_quotes_str = malloc(1);
	no_quotes_str[0] = '\0';
	return no_quotes_str;
}

char	**strings_without_quotes(char *words, char **envp)
{
	int		i;
	int		k;
	char	**no_quotes_str;

	no_quotes_str = malloc((count_strings(words) + 1) * sizeof(char *));
	k = 0;
	i = 0;
	while (words[i])
	{
		if ((words[i] == '\"' && words[i + 1] == '\"') || (words[i] == '\''
				&& words[i + 1] == '\''))
		{
			no_quotes_str[k] = empty_string(no_quotes_str[k]);
			k++;
			i = i + 2;
		}
		else if ((words[i] == '\"' && words[i + 1] != '\"')) //expand;
		{
			no_quotes_str[k] = fill_word_with_d_quotes(no_quotes_str[k],
					&words[i]);
			no_quotes_str[k] = fill_expand(no_quotes_str[k], envp);
			i++;
			while (words[i] && words[i] != '\"')
				i++;
			if (words[i])
				i++;
			k++;
		}
		else if ((words[i] == '\'' && words[i + 1] != '\''))
		{
			no_quotes_str[k] = fill_word_with_s_quotes(no_quotes_str[k],
					&words[i]);
			i++;
			while (words[i] && words[i] != '\"')
				i++;
			if (words[i])
				i++;
			k++;
		}
		else if (words[i] != '\"' && words[i] != '\'') //expand
		{
			no_quotes_str[k] = fill_word_without_quotes(no_quotes_str[k],
					&words[i]);
			no_quotes_str[k] = fill_expand(no_quotes_str[k], envp);
			while (words[i] && words[i] != '\"' && words[i] != '\'')
				i++;
			k++;
		}
	}
	no_quotes_str[k] = NULL;
	return (no_quotes_str);
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

void	print_info_without_quotes(t_token *ptr, char **envp)
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
	exit_status = 1;
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
			print_info_without_quotes(ptr, envp);
		}
	}
	free(cmd);
	free(command);
	system("leaks minishell");
	return (0);
}

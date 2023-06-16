/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:53:19 by mhassani          #+#    #+#             */
/*   Updated: 2023/06/16 22:20:28 by mhassani         ###   ########.fr       */
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
			if(words[i])
				i++;
			count++;
		}
		else if (words[i] == '\'' && words[i + 1] != '\'')
		{
			i++;
			while (words[i] && words[i] != '\'')
				i++;
			if(words[i])
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
			if(words[i])
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
			if(words[i])
				i++;
		}
		else if (words[i] != '\"' && words[i] != '\'')      //=> i should check for expand;
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

char	**strings_without_quotes(char *words, char **envp)
{
	int		i;
	int		j;
	int		k;
	char	**no_quotes_str;
	char	*expand;
	int		size;

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
		else if ((words[i] == '\"' && words[i + 1] != '\"'))       //=> i should check for expand; 
		{
			j = 0;
			i++;
			no_quotes_str[k] = malloc(word_len(&words[i]) + 1);
			while (words[i] && words[i] != '\"')
				no_quotes_str[k][j++] = words[i++];
			no_quotes_str[k][j] = '\0';
			if (ft_expand_value(no_quotes_str[k], envp))
			{
				j = 0;
				int l = 0;
				size = (ft_strlen(ft_expand_value(no_quotes_str[k], envp)) + 1);
				char *expand = ft_expand_value(no_quotes_str[k], envp);
				no_quotes_str[k] = malloc(size + 1);
				while (expand[l])
					no_quotes_str[k][j++] = expand[l++];
				no_quotes_str[k][j] = '\0';
			}
			k++;
			if(words[i])
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
			if(words[i])
				i++;
		}
		else if (words[i] != '\"' && words[i] != '\'')      //=> i should check for expand;
		{
			j = 0;
			no_quotes_str[k] = malloc(len(&words[i]) + 1);
			while (words[i] && words[i] != '\"' && words[i] != '\'')
				no_quotes_str[k][j++] = words[i++];
			no_quotes_str[k][j] = '\0';
			if (ft_expand_value(no_quotes_str[k], envp))
			{
				j = 0;
				int l = 0;
				size = (ft_strlen(ft_expand_value(no_quotes_str[k], envp)) + 1);
				char *expand = ft_expand_value(no_quotes_str[k], envp);
				no_quotes_str[k] = malloc(size + 1);
				while (expand[l])
					no_quotes_str[k][j++] = expand[l++];
				no_quotes_str[k][j] = '\0';
				j = 1;
			}
			k++;
		}
	}
	no_quotes_str[k] = NULL;
	return (no_quotes_str);
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

void	print_info(t_token *ptr, char **envp)
{
	int i;
	t_token *data;
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
			command = space_arround_red(cmd); //add space before and after (< / >);
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

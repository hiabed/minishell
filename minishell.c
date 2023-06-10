/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:53:19 by mhassani          #+#    #+#             */
/*   Updated: 2023/06/10 15:37:08 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_strings(char *words)
{
	int	i;
	int	j;
	int	count;

	j = ft_strlen(words);
	count = 0;
	i = 0;
	while (words[i] && words[i + 1])
	{
		if (words[i + 1] && words[i] == '\"' && words[i + 1] == '\"')
		{
			count++;
			i = i + 2;
		}
		else if (words[i + 1] && (words[i] == '\"' && words[i + 1] != '\"'))
		{
			i++;
			while (words[i] && words[i] != '\"')
				i++;
			count++;
			i++;
		}
		else if (words[i] != '\"')
		{
			while (words[i] && words[i] != '\"')
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

char	**strings_without_quotes(char *words)
{
	int		i;
	int		j;
	int		k;
	char	**no_quotes_str;

	no_quotes_str = malloc((count_strings(words) + 1) * sizeof(char *));
	k = 0;
	i = 0;
	while (words[i] && words[i + 1])
	{
		if (words[i] == '\"' && words[i + 1] == '\"')
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
			i++;
		}
		else
		{
			j = 0;
			no_quotes_str[k] = malloc(word_len(&words[i]) + 1);
			while (words[i] && words[i] != '\"')
				no_quotes_str[k][j++] = words[i++];
			no_quotes_str[k][j] = '\0';
			k++;
		}
	}
	no_quotes_str[k] = NULL;
	return (no_quotes_str);
}

char	*join_strings(char *words)
{
	int		i;
	char	*joined_string;
	char	**to_be_joined;
	char	*temp;

	i = 0;
	joined_string = NULL;
	to_be_joined = strings_without_quotes(words);
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

int	main(void)
{
	char	*cmd;
	char	*command;
	char	**tokens;
	char	**words;
	t_data	*data;
	t_token	*ptr;
	t_token	*data2;
	int		j;

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
			command = ft_strdup(cmd); //add space before and after (< / >);
			replace_pipe_in_quotes(command);
			tokens = split_with_pipe(command);
			j = 0;
			ptr = NULL;
			while (tokens[j])
			{
				replace_space_in_quotes(tokens[j]);
				words = split_with_space(tokens[j]);
				ft_lstadd_token(&ptr, ft_lstnew_token(words));
				j++;
			}
			data2 = ptr;
			while (data2)
			{
				j = 0;
				printf("------------\n");
				if(data2->cmd)
				{
					data2->cmd = join_strings(data2->cmd);
					printf("cmd: %s\n", data2->cmd);
				}
				while (data2->arg[j])
				{
					data2->arg[j] = join_strings(data2->arg[j]);
					printf("arg: %s\n", data2->arg[j]);
					j++;
				}
				while (data2->red)
				{
					printf("type: %d\n", data2->red->type);
					printf("limiter: %s\n", data2->red->limiter);
					printf("file: %s\n", data2->red->file);
					data2->red = data2->red->next;
				}
				data2 = data2->next;
			}
		}
	}
	free(cmd);
	free(command);
	system("leaks minishell");
	return (0);
}

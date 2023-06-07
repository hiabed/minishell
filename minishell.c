/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:53:19 by mhassani          #+#    #+#             */
/*   Updated: 2023/06/07 21:27:52 by mhassani         ###   ########.fr       */
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
		if (words[i] == '\"' && words[i + 1] == '\"')
		{
			count++;
			i = i + 2;
		}
		else if ((words[i] == '\"' && words[i + 1] != '\"'))
		{
			i++;
			while (words[i] && words[i] != '\"')
				i++;
			count++;
			i++;
		}
		else
		{
			while (words[i] && words[i] != '\"')
				i++;
			count++;
		}
	}
	return (count);
}

int	quotes_len(char *words)
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
	char	**empty_str;
	empty_str = malloc((count_strings(words) + 1) * sizeof(char *));
	k = 0;
	i = 0;
	while (words[i])
	{
		if (words[i] == '\"' && words[i + 1] == '\"')
		{
			empty_str[k] = malloc(1);
			empty_str[k][0] = '\0';
			k++;
			i = i + 2;
		}
		else if ((words[i] == '\"' && words[i + 1] != '\"'))
		{
			j = 0;
			i++;
			empty_str[k] = malloc(quotes_len(&words[i]) + 1);
			while (words[i] && words[i] != '\"')
				empty_str[k][j++] = words[i++];
			empty_str[k][j] = '\0';
			k++;
			i++;
		}
		else
		{
			j = 0;
			empty_str[k] = malloc(quotes_len(&words[i]) + 1);
			while (words[i] && words[i] != '\"')
				empty_str[k][j++] = words[i++];
			empty_str[k][j] = '\0';
			k++;
		}
	}
	empty_str[k] = NULL;
	return (empty_str);
}

char	*join_empty_strings(char *words)
{
	int		i;
	char	*joined_string;
	char	**to_be_joined;
	char	*temp;

	i = 0;
	joined_string = NULL;
	to_be_joined = strings_without_quotes(words);
	// printf("%s\n", to_be_joined[0]);
	if (to_be_joined[i])
	{
		// Start with the first string
		joined_string = to_be_joined[i];
		// Iterate from the second string onwards
		while (to_be_joined[i + 1])
		{
			temp = ft_strjoin(joined_string, to_be_joined[i + 1]);
			joined_string = temp;
			i++;
		}
	}
	// printf("joined_string: %s\n", joined_string);
	return (joined_string);
}

int	count_args(char **words)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	printf("wordsss[%d]: %s\n", i, words[i]);
	while (words[i])
	{
		if (words[i][0] == '>' || words[i][0] == '<')
			i = i + 2;
		else if (i == 0)
			i++;
		else
		{
			k++;
			i++;
		}
	}
	return (k);
}

char	**ft_arg(char **words)
{
	char	**args;
	int		i;
	int		k;
	int		cmd;

	k = count_args(words);
	args = malloc(sizeof(char *) * (k + 1));
	i = 0;
	k = 0;
	cmd = 0;
	if(!words[i])
		return NULL;
	while (words[i])
	{
		while (words[i] && (words[i][0] == '>' || words[i][0] == '<'))
			i = i + 2;
		if (!cmd && (words[i][0] != '>' && words[i][0] != '<'))
		{
			cmd++;
			i++;
		}
		while (words[i] && (cmd > 0) && (words[i][0] != '>'
				&& words[i][0] != '<'))
			args[k++] = words[i++];
	}
	args[k] = NULL;
	i = 0;
	while(args[i])
	{
		args[i] = join_empty_strings(args[i]);
		i++;
	}
	return (args);
}

char	*ft_cmd(char **words)
{
	int	i;

	i = 0;
	if (words[i] && words[i][0] != '>' && words[i][0] != '<')
	{
		printf("==>1\n");
		words[i] = join_empty_strings(words[i]);
		return (words[i]);
	}
	while (words[i])
	{
		if (words[i][0] == '\"')
		{
			printf("2\n");
			words[i] = join_empty_strings(words[i]);
			return (words[i]);
		}
		if (words[i][0] != '>' && words[i][0] != '<')
		{
			printf("==>3\n");
			words[i] = join_empty_strings(words[i]);
			return (words[i]);
		}
	}
	return (NULL);
}

void	ft_lstadd_token(t_token **lst, t_token *new)
{
	t_token	*ptr;

	ptr = *lst;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}

t_token	*ft_lstnew_token(char **words)
{
	t_token	*head;
	int		i;

	i = 0;
	head = malloc(sizeof(t_token));
	if (!head)
		return (NULL);
	head->red = ft_redirections(words);
	head->cmd = ft_cmd(words);
	head->arg = ft_arg(words);
	head->next = NULL;
	return (head);
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
	// int		i;
	int		j;

	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	while (1)
	{
		cmd = readline("minishell-3.2$ ");
		ptr = NULL;
		if (!cmd)
		{
			printf("exit\n");
			exit(EXIT_FAILURE);
		}
		add_history(cmd);
		data->error = 0;
		data->flag = 0;
		syntax_errors(cmd, data);
		if (data->error == 0)
		{
			command = ft_strdup(cmd); //add space before and after (< / >);
			replace_pipe_in_quotes(command);
			tokens = split_with_pipe(command);
			j = 0;
			while (tokens[j])
			{
				// printf("===>token[%d]: %s\n", j, tokens[j]);
				replace_space_in_quotes(tokens[j]);
				words = split_with_space(tokens[j]);
				// remove_quotes(words);
				// i = 0;
				// while (words[i])
				// {
				// 	words[i] = join_empty_strings(words[i]);
				// 	i++;
				// }
				ft_lstadd_token(&ptr, ft_lstnew_token(words));
				j++;
			}
			data2 = ptr;
			while (data2)
			{
				j = 0;
				printf("------------\n");
				printf("cmd: %s\n", data2->cmd);
				while (data2->arg[j])
				{
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

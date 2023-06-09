/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:45:14 by mhassani          #+#    #+#             */
/*   Updated: 2023/06/09 21:51:09 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(char **words)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (words[i])
	{
		if (i == 0)
			i++;
		else if (words[i + 1] && (words[i][0] == '>' || words[i][0] == '<'))
			i = i + 2;
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
	int		j;
	int		cmd;

	cmd = 0;
	k = count_args(words);
	i = 0;
	j = 0;
	args = malloc(sizeof(char *) * (k + 1));
	while (words[i] && k)
	{
		if (words[i + 1] && (words[i][0] == '>' || words[i][0] == '<'))
			i++;
		else if (i == 0)
			cmd++;
		else if (words[i] && j < k)
		{
			words[i] = join_empty_strings(words[i]);
			args[j++] = words[i];
		}
		i++;
	}
	args[j] = NULL;
	return (args);
}

char	*ft_cmd(char **words)
{
	int	i;

	i = 0;
	if (words[i] && words[i][0] != '>' && words[i][0] != '<')
	{
		words[i] = join_empty_strings(words[i]);
		return (words[i]);
	}
	while (words[i])
	{
		if (words[i][0] == '\"')
		{
			words[i] = join_empty_strings(words[i]);
			return (words[i]);
		}
		if (words[i][0] != '>' && words[i][0] != '<')
		{
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
	t_token *head;
	int i;

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
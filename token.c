/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:45:14 by mhassani          #+#    #+#             */
/*   Updated: 2023/07/07 20:47:53 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(char **words)
{
	int	i;
	int	k;
	int	cmd;

	cmd = 0;
	i = 0;
	k = 0;
	while (words[i])
	{
		if (words[i + 1] && (words[i][0] == '>' || words[i][0] == '<'))
			i++;
		else if (!cmd && words[i][0] != '>' && words[i][0] != '<')
			cmd++;
		else if (cmd && (words[i][0] != '>' && words[i][0] != '<'))
			k++;
		i++;
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
		else if (!cmd && words[i][0] != '>' && words[i][0] != '<')
			cmd++;
		else if (cmd && (words[i][0] != '>' && words[i][0] != '<'))
			args[j++] = ft_strdup(words[i]);
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
		return (ft_strdup(words[i]));
	while (words[i])
	{
		if (words[i][0] != '>' && words[i][0] != '<')
			return (ft_strdup(words[i]));
		if (words[i + 1] && (words[i][0] != '>' || words[i][0] != '<'))
			i++;
		i++;
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

t_token	*ft_lstnew_token(char **words, t_env *envp)
{
	t_token	*head;

	head = malloc(sizeof(t_token));
	if (!head)
		return (NULL);
	head->cmd = ft_cmd(words);
	head->arg = ft_arg(words);
	head->red = ft_redirections(words, envp);
	head->next = NULL;
	return (head);
}

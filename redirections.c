/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 22:14:50 by mhassani          #+#    #+#             */
/*   Updated: 2023/06/03 14:49:31 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_red(t_redirection **lst, t_redirection *new)
{
	t_redirection	*ptr;

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

char	*ft_file_name(char **words, int type)
{
	int	i;

	i = 0;
	if (words[i] && words[i + 1] && (type == 1 || type == 2 || type == 3))
		return (words[i + 1]);
	return (NULL);
}

char	*ft_limiter_name(char **words, int type)
{
	int	i;

	i = 0;
	if (words[i] && words[i + 1] && type == 4)
		return (words[i + 1]);
	return (NULL);
}

int	ft_number_type(char **words)
{
	if (words[0][0] == '<' && words[0][1] == '<')
		return (4);
	if (words[0][0] == '>' && words[0][1] == '>')
		return (3);
	else if (words[0][0] == '<')
		return (2);
	else if (words[0][0] == '>')
		return (1);
	return (0);
}

t_redirection	*ft_lstnew_red(char **words)
{
	t_redirection	*red_node;
	
	red_node = malloc(sizeof(t_redirection));
	if (!red_node)
		return (NULL);
	red_node->type = ft_number_type(words);
	red_node->limiter = ft_limiter_name(words, red_node->type);
	red_node->file = ft_file_name(words, red_node->type);
	red_node->next = NULL;
	return (red_node);
}

t_redirection	*ft_redirections(char **words)
{
	int i = 0;
	t_redirection *lst;
    t_redirection *ptr;
    lst = NULL;
    ptr = malloc(sizeof(t_redirection));
    ptr->type = 0;
	while (words[i])
	{
		if(words[i][0] == '>' || words[i][0] == '<')
			ft_lstadd_red(&lst, ft_lstnew_red(&words[i]));
		i++;
	}
	return (lst);
}
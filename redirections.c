/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 22:14:50 by mhassani          #+#    #+#             */
/*   Updated: 2023/06/09 16:45:59 by mhassani         ###   ########.fr       */
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

char	*ft_file_name(char *words, int type)
{
	int	i;

	i = 0;
	if (words && (type == 1 || type == 2 || type == 3))
	{
		words = join_empty_strings(words);
		return (words);
	}
	return (NULL);
}

char	*ft_limiter_name(char *words, int type)
{
	if (words && type == 4)
	{
		words = join_empty_strings(words);
		return (words);
	}
	return (NULL);
}

int	ft_number_type(char *words)
{
	if (words[0] == '<' && words[1] == '<')
		return (4);
	if (words[0] == '>' && words[1] == '>')
		return (3);
	else if (words[0] == '<')
		return (2);
	else if (words[0] == '>')
	{
		printf("hhhhhhhh\n");
		return (1);
	}
	return (0);
}

t_redirection	*ft_lstnew_red(char **words)
{
	t_redirection	*red_node;

	red_node = malloc(sizeof(t_redirection));
	if (!red_node)
		return (NULL);
	printf("words[i]: %s\n", *words);
	red_node->type = ft_number_type(*words);
	words++;
	red_node->limiter = ft_limiter_name(*words, red_node->type);
	red_node->file = ft_file_name(*words, red_node->type);
	red_node->next = NULL;
	return (red_node);
}

t_redirection	*ft_redirections(char **words)
{
	t_redirection *lst;
	lst = NULL;
	while (*words)
	{
		if (*words[0] == '>' || *words[0] == '<')
		{
			printf("first words[i]: %s\n", *words);
			ft_lstadd_red(&lst, ft_lstnew_red(words));
		}
		words++;
	}
	return (lst);
}
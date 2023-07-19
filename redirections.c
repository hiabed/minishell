/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 22:14:50 by mhassani          #+#    #+#             */
/*   Updated: 2023/07/19 16:05:03 by mhassani         ###   ########.fr       */
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

char	*ft_file_name(char *words, t_env *envp, int type)
{
	int	i;

	i = 0;
	if (words[i] && (type == 1 || type == 2 || type == 3))
	{
		words = join_strings_to_be_one(words, envp);
		return (words);
	}
	return (NULL);
}

char	*ft_limiter_name(char *words, int type)
{
	int	i;

	i = 0;
	if (words[i] && type == 4)
	{
		words = join_heredoc_to_be_one(words);
		return (words);
	}
	return (NULL);
}

t_redirection	*ft_lstnew_red(char **words, t_env *envp)
{
	t_redirection	*red_node;

	red_node = malloc(sizeof(t_redirection));
	if (!red_node)
		return (NULL);
	red_node->type = ft_number_type(*words);
	words++;
	red_node->limiter = ft_limiter_name(*words, red_node->type);
	red_node->file = ft_file_name(*words, envp, red_node->type);
	red_node->next = NULL;
	return (red_node);
}

t_redirection	*ft_redirections(char **words, t_env *envp)
{
	t_redirection	*lst;
	int				i;
	t_redirection	*red;

	lst = NULL;
	i = 0;
	while (words[i])
	{
		if (words[i][0] == '>' || words[i][0] == '<')
		{
			red = ft_lstnew_red(&words[i], envp);
			ft_lstadd_red(&lst, red);
		}
		i++;
	}
	return (lst);
}

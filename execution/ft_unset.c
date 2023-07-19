/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:45:57 by mkatfi            #+#    #+#             */
/*   Updated: 2023/07/19 22:56:33 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cheack_arg_unset(char *s)
{
	int	i;

	i = 0;
	if (ft_isdigit(s[0]) == 1)
		return (0);
	while (s[i])
	{
		if (ft_isalnum(s[i]) == 0 && (s[i] != '_'))
			return (0);
		i++;
	}
	return (1);
}

void	delet_any_node(t_env *curr, t_env *pre, char *s)
{
	while (curr != NULL)
	{
		if (!ft_strcmp(s, "_"))
			break ;
		else if (ft_strcmp(curr->key, s) == 0)
		{
			pre->next = curr->next;
			free(curr->key);
			free(curr->valuer);
			free(curr->content);
			free(curr);
			break ;
		}
		pre = curr;
		curr = curr->next;
	}
}

void	to_be_comtinued_unset(t_env **p, char *s)
{
	t_env	*curr;
	t_env	*pre;

	pre = NULL;
	curr = *p;
	if (curr && ft_strcmp(curr->key, s) == 0)
	{
		*p = (*p)->next;
		free(curr->key);
		free(curr->valuer);
		free(curr->content);
		free(curr);
		return ;
	}
	delet_any_node(curr, pre, s);
}

void	ft_unset(t_env **p, char **s)
{
	int	i;

	i = 0;
	g_g.exit_status = 0;
	while (s[i])
	{
		if (!cheack_arg_unset(s[i]))
		{
			ft_error_3(s[i], 1);
			g_g.exit_status = 1;
		}
		i++;
	}
	i = 0;
	while (s[i])
	{
		to_be_comtinued_unset(p, s[i]);
		i++;
	}
}

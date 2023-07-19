/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 13:44:32 by mkatfi            #+#    #+#             */
/*   Updated: 2023/07/19 16:02:44 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	aray(t_env *a, int i)
{
	t_env	*tmp;
	t_env	*t;
	char	*small;

	tmp = a;
	while (tmp->index != -1)
		tmp = tmp->next;
	small = tmp->key;
	tmp = a;
	while (tmp)
	{
		if (tmp->index == -1 && ft_strcmp(small, tmp->key) >= 0)
		{
			small = tmp->key;
			t = tmp;
		}
		tmp = tmp->next;
	}
	t->index = i;
}

void	writor(t_env *ptr1, int fd)
{
	ft_putstr_fd("declare -x ", fd);
	ft_putstr_fd(ptr1->key, fd);
	if (ptr1->valuer != NULL)
	{
		ft_putchar_fd('=', fd);
		ft_putchar_fd('\"', fd);
		ft_putstr_fd(ptr1->valuer, fd);
		ft_putchar_fd('\"', fd);
	}
	ft_putchar_fd('\n', fd);
}

void	continued_sort_nb(int i, t_env *ptr, t_env *a, int fd)
{
	t_env	*ptr1;

	i = 0;
	ptr = a;
	while (ptr)
	{
		ptr1 = a;
		while (ptr1)
		{
			if (i == ptr1->index)
				writor(ptr1, fd);
			ptr1 = ptr1->next;
		}
		i++;
		ptr = ptr->next;
	}
}

void	sort_nb(t_env *a, int fd)
{
	t_env	*ptr;
	int		i;

	ptr = a;
	i = 0;
	while (ptr != NULL)
	{
		aray(a, i++);
		ptr = ptr->next;
	}
	continued_sort_nb(i, ptr, a, fd);
	while (a)
	{
		a->index = -1;
		a = a->next;
	}
}

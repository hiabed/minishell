/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:17:11 by mkatfi            #+#    #+#             */
/*   Updated: 2023/07/19 16:02:40 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cheack_arg(char *s)
{
	int	i;

	i = 0;
	if (s[i] && ft_isdigit(s[0]) == 1)
	{
		ft_error(s, 1);
		g_g.exit_status = 1;
		return (0);
	}
	while (s[i] && s[i] != '=')
	{
		if (s[i] == '+' && s[i + 1] == '=')
			return (1);
		if ((ft_isalnum(s[i]) == 0) && (s[i] != '_'))
		{
			ft_error(s, 1);
			g_g.exit_status = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

char	*str_join(char *s1, char *s2)
{
	char	*g;
	int		i;
	int		j;

	i = 0;
	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		s2 = ft_strdup("");
	g = malloc(sizeof(char) * (ft_strlen(s2) + ft_strlen(s1)) + 1);
	if (!g)
	{
		free(s1);
		return (NULL);
	}
	while (s1 && s1[i])
	{
		g[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
		g[i++] = s2[j++];
	g[i] = '\0';
	return (g);
}

int	is_he_in_env(t_env *a, char *s)
{
	while (a)
	{
		if (ft_strcmp(a->key, s) == 0)
			return (1);
		a = a->next;
	}
	return (0);
}

void	riblce_v(t_env *a, char *s, char *c)
{
	while (a)
	{
		if (ft_strcmp(a->key, s) == 0)
		{
			if (c != NULL)
			{
				free(a->valuer);
				a->valuer = ft_strdup(c);
			}
			else
			{
				free(a->valuer);
				a->valuer = NULL;
			}
			return ;
		}
		a = a->next;
	}
}

int	icale(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
		{
			if (s[i - 1] == '+')
				return (2);
			return (1);
		}
		i++;
	}
	return (0);
}

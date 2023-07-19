/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ex_continued.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 13:33:58 by mkatfi            #+#    #+#             */
/*   Updated: 2023/07/19 16:02:48 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_envrment(t_env *p)
{
	char	**d;
	int		n;
	t_env	*tem;

	n = 0;
	tem = p;
	while (tem)
	{
		tem = tem->next;
		n++;
	}
	d = malloc(sizeof(char *) * (n + 1));
	n = 0;
	while (p)
	{
		d[n] = p->content;
		p = p->next;
		n++;
	}
	d[n] = NULL;
	return (d);
}

char	*get_path(t_env *p)
{
	t_env	*ptr;

	ptr = p;
	while (ptr)
	{
		if (ft_strcmp("PATH", ptr->key) == 0)
			return (ptr->valuer);
		ptr = ptr->next;
	}
	return (NULL);
}

char	**join_cmd(char *d, char **s)
{
	char	**p;
	int		i;
	int		j;

	i = 0;
	j = 1;
	while (s && s[i])
		i++;
	if (s && *s)
	{
		p = malloc(sizeof(char *) * (i + 2));
		i = 0;
		p[0] = ft_strdup(d);
		while (s && s[i])
			p[j++] = ft_strdup(s[i++]);
		p[j] = NULL;
		return (p);
	}
	p = malloc(sizeof(char *) * (2));
	p[0] = ft_strdup(d);
	p[1] = NULL;
	return (p);
}

char	*get_path_cmd(t_env *p, char *d, char **s)
{
	int	i;

	g_g.g = get_path(p);
	g_g.c = ft_split(g_g.g, ':');
	g_g.jo = join_cmd(d, s);
	g_g.gv = get_envrment(p);
	if (access(d, X_OK) == 0)
		execve(d, g_g.jo, g_g.gv);
	i = 0;
	if (g_g.c == NULL || *g_g.c == NULL)
		return (NULL);
	while (g_g.c && g_g.c[i])
	{
		g_g.syt = ft_strjoin(g_g.c[i], "/");
		g_g.buff = ft_strjoin(g_g.syt, d);
		if (access(g_g.buff, F_OK) == 0)
			return (g_g.buff);
		free(g_g.buff);
		free(g_g.syt);
		i++;
	}
	return (NULL);
}

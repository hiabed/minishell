/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 22:39:28 by mkatfi            #+#    #+#             */
/*   Updated: 2023/06/22 20:42:16 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env(t_env **ptr, char *s)
{
	t_env	*p;

	p = *ptr;
	while (p)
	{
		if (ft_strcmp(p->key, s) == 0)
			return (p->valuer);
		p = p->next;
	}
	return (NULL);
}

char	*chaeck(t_env **ptr, char *s, char *k)
{
	t_env	*p;

	p = *ptr;
	while (p)
	{
		if (ft_strcmp(p->key, s) == 0)
			p->valuer = k;
		p = p->next;
	}
	return (NULL);
}

void	ft_cd(char **s, t_env **p)
{
	char	*path_pwd;
	char	*bag;

	path_pwd = ft_pwd(0);
	if (!s[0])
	{
		path_pwd = get_env(p, "HOME");
		chaeck(p, "OLDPWD", ft_pwd(0));
		if (chdir(path_pwd) == -1)
		{
			write(2, "ERROR\n", 6);
			g_g.exit_status = 1;
		}
		chaeck(p, "PWD", ft_pwd(0));
		return ;
	}
	if (s != NULL)
	{
		bag = ft_strjoin("/", *s);
		path_pwd = ft_strjoin(path_pwd, bag);
		chaeck(p, "OLDPWD", ft_pwd(0));
		if (chdir(path_pwd) == -1)
		{
			write(1, "ERROR\n", 6);
			g_g.exit_status = 1;
		}
		chaeck(p, "PWD", ft_pwd(0));
		return ;
	}
}

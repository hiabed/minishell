/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 22:39:28 by mkatfi            #+#    #+#             */
/*   Updated: 2023/07/19 16:02:09 by mhassani         ###   ########.fr       */
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
		{
			free(p->valuer);
			p->valuer = ft_strdup(k);
		}
		p = p->next;
	}
	return (NULL);
}

void	ft_cd1(char *path_pwd, char *home, t_env **p)
{
	path_pwd = ft_pwd(0, 0);
	home = get_env(p, "HOME");
	chaeck(p, "OLDPWD", path_pwd);
	free(path_pwd);
	if (chdir(home) == -1)
	{
		ft_error(" HOME ", 3);
		g_g.exit_status = 1;
	}
	home = ft_pwd(0, 0);
	chaeck(p, "PWD", home);
	g_g.exit_status = 0;
	free(home);
}

void	ft_cd2(char *path_pwd, char *old_pwd, char **s, t_env **p)
{
	path_pwd = ft_pwd(0, 0);
	if (s[0][0] == '/' && s[0][1] == '\0')
	{
		free(path_pwd);
		path_pwd = ft_strdup(*s);
	}
	else
	{
		free(path_pwd);
		path_pwd = ft_strdup(*s);
	}
	old_pwd = ft_pwd(0, 0);
	chaeck(p, "OLDPWD", old_pwd);
	if (chdir(path_pwd) == -1 && s[0][0] != '.')
	{
		ft_error(path_pwd, 2);
		g_g.exit_status = 1;
	}
	chaeck(p, "PWD", path_pwd);
	free(path_pwd);
	free(old_pwd);
	g_g.exit_status = 0;
}

void	ft_cd(char **s, t_env **p)
{
	char	*path_pwd;
	char	*old_pwd;
	char	*home;

	path_pwd = NULL;
	old_pwd = NULL;
	home = NULL;
	if (!s[0])
	{
		ft_cd1(path_pwd, home, p);
		return ;
	}
	if (s != NULL)
	{
		ft_cd2(path_pwd, old_pwd, s, p);
		return ;
	}
}

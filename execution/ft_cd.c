/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 22:39:28 by mkatfi            #+#    #+#             */
/*   Updated: 2023/07/17 13:55:43 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"
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

void	ft_cd(char **s, t_env **p)
{
	char	*path_pwd;
	char	*old_pwd;
	char	*home;
	char	*bag;

	if (!s[0])
	{
		path_pwd = ft_pwd(0, 0);
		home = get_env(p, "HOME");
		chaeck(p, "OLDPWD", path_pwd);
		free(path_pwd);
		if (chdir(home) == -1)
		{
			ft_Error(" HOME ", 2);
			g_g.exit_status = 1;
		}
		home = ft_pwd(0,0);
		chaeck(p, "PWD", home);
		g_g.exit_status = 0;
		free(home);
		return ;
	}

	if (s != NULL)
	{
		path_pwd = ft_pwd(0, 0);
		if (s[0][0] == '/' && s[0][1] == '\0')
		{		
			free(path_pwd);
			path_pwd = ft_strdup(*s);
		}
		else
		{
			if (s[0][0] != '/' && s[0][1] != '\0')
				bag = ft_strjoin("/", *s);
			else
				bag = ft_strdup(*s);
			path_pwd = ft_strjoin_f(path_pwd, bag);
			free(bag);
		}
		old_pwd = ft_pwd(0,0);
		chaeck(p, "OLDPWD", old_pwd);
		if (chdir(path_pwd) == -1 && s[0][0] != '.')
		{
			ft_Error(path_pwd, 2);
			g_g.exit_status = 1;
		}
		chaeck(p, "PWD", path_pwd);
		free(path_pwd);
		free(old_pwd);
		g_g.exit_status = 0;
		return ;
	}
}

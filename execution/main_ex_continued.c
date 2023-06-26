/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ex_continued.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkatfi <mkatfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 13:33:58 by mkatfi            #+#    #+#             */
/*   Updated: 2023/06/25 18:59:26 by mkatfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

char** get_envrment(t_env* p)
{
    	char** d;
		int n = 0;
		t_env* tem;

		tem = p;
		while (tem)
		{
			tem = tem->next;
			n++;
		}
		d = malloc(sizeof(char*) * (n + 1));
		n = 0;
		while (p)
		{
			d[n] = p->content;
			p = p->next;
			n++;
		}
        d[n] = NULL;
        return(d);
}

char* get_path(t_env* p)
{
    while (p)
    {
        if (ft_strcmp("PATH", p->key) == 0)
            return(p->valuer);
        p = p->next;
    }
    return(NULL);
}

char** join_cmd(char* d, char** s)
{
    char** p;
    if (s && *s)
    {
        p = malloc(sizeof(char*) * (3));
        p[0] = ft_strdup(d);
        p[1] = ft_strdup(s[0]);
        return(p[2] = NULL, p);
    }
    p = malloc(sizeof(char*) * (2));
    p[0] = ft_strdup(d);
    p[1] = NULL;
    return(p);
}

char* get_path_cmd(t_env* p, char* d, char** s)
{
    char* g;
    char** c;
    char* syt;
    char* buff;
    g = get_path(p);
    c = ft_split(g, ':');
    if (access(d, X_OK) == 0)
        execve(d, join_cmd(d, s), get_envrment(p));
    int i = 0;
    if (c == NULL || *c == NULL)
        return(NULL);
    while (c && c[i])
    {
        syt = ft_strjoin(c[i], "/");
        buff = ft_strjoin(syt, d);
        if (access(buff, F_OK) == 0)
            return(buff);
        i++;
    }
    return(NULL);
}

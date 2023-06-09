/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ex_continued.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 13:33:58 by mkatfi            #+#    #+#             */
/*   Updated: 2023/07/10 16:21:37 by mhassani         ###   ########.fr       */
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
    t_env *ptr = p;
    while (ptr)
    {
        if (ft_strcmp("PATH", ptr->key) == 0)
            return(ptr->valuer);
        ptr = ptr->next;
    }
    return(NULL);
}

char** join_cmd(char* d, char** s)
{
    char** p;
    int i = 0;
    int j = 1;
    while (s && s[i])
        i++;
    if (s && *s)
    {
        p = malloc(sizeof(char*) * (i + 2));
        i = 0;
        p[0] = ft_strdup(d);
        while (s && s[i])
            p[j++] = ft_strdup(s[i++]);
        p[j] = NULL;
        return(p);
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
    char** jo;
    char** gv;
    
    g = get_path(p);
    c = ft_split(g, ':');
    jo = join_cmd(d, s);
    gv = get_envrment(p);
    if (access(d, X_OK) == 0)
        execve(d, jo, gv);
    int i = 0;
    if (c == NULL || *c == NULL)
        return(NULL);
    while (c && c[i])
    {
        syt = ft_strjoin(c[i], "/");
        buff = ft_strjoin(syt, d);
        if (access(buff, F_OK) == 0)
            return(buff);
        free(buff);
        free(syt);
        i++;
    }
    // freepath(jo);
    // freepath(gv);
    // free(buff);
    // free(syt);
    return(NULL);
}

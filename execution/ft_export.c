/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 16:40:11 by mkatfi            #+#    #+#             */
/*   Updated: 2023/07/18 21:12:36 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

char* valuer_of_key(t_env* a, char* s)
{
    while (a)
    {
        if (ft_strcmp(a->key, s) == 0)
        {
            return(a->valuer);
        }
        a = a->next;
        }
        return(NULL);
}

void to_be_contined(int i, t_env *p, char **s)
{
    char** a;
    char* valuer;
    
    a = key_valu(s[i]);
    if (is_he_in_env(p, a[0]) == 1)
    {
        valuer = valuer_of_key(p, a[0]);
        char* val = ft_strjoin(valuer, a[1]);
        if (icale(s[i]) == 2)
            riblce_v(p, a[0], val);
        else if (icale(s[i]) == 1)
            riblce_v(p, a[0], a[1]);
        free(val);
    }
    else if (is_he_in_env(p, a[0]) == 0)
    {
        if (icale(s[i]) == 1 || icale(s[i]) == 2)
        {
            printf("HERE1\n");
            ft_lstadd_back_env(&p, ft_lstnew_env(s[i]));
        }
        else if (icale(s[i]) == 0)
        {
            printf("HERE2\n");
            printf("before\n");
            printf("p: %p\n", p);
            ft_lstadd_back_env(&p, ft_lstnew_env(s[i]));
            printf("after\n");
            printf("p: %p\n", p);
            printf("key: %s val: %s\n", p->key, p->valuer);
            free(a[1]);
            a[1] = NULL;
            riblce_v(p, a[0], a[1]);
        }
    }
    // printf("p: %p\n", p);
    freepath(a);
}

void ft_export(char **s, t_env *p, int fd)
{
    int i ;
    g_g.exit_status = 0;
    if (s == NULL || *s == NULL)
        sort_nb(p, fd);
    else
    {
        i = 0;
        while (s && s[i])
        {
            if (!cheack_arg(s[i]))
            {
                i++;
                continue;
            }
            else if (cheack_arg(s[i]))
                to_be_contined(i, p, s);
            i++;
        }
    }
}

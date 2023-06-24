/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 16:40:11 by mkatfi            #+#    #+#             */
/*   Updated: 2023/06/23 19:06:46 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
        char* val = str_join(valuer, a[1]);     
        if (icale(s[i]) == 2)
            riblce_v(p, a[0], val);
        if (icale(s[i]) == 1)
            riblce_v(p, a[0], a[1]);
    }
    if (is_he_in_env(p, a[0]) == 0)
    {
        if (icale(s[i]) == 1 || icale(s[i]) == 2)
        {
            ft_lstadd_back_env(&p, ft_lstnew_env(s[i]));
        }
        if (icale(s[i]) == 0)
        {
            ft_lstadd_back_env(&p, ft_lstnew_env(s[i]));
            a[1] = NULL;
            riblce_v(p, a[0], a[1]);
        }
    }
}

void ft_export(char **s, t_env *p)
{
    int i ;
 
    if (s == NULL || *s == NULL)
        sort_nb(p);
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
    // while (p != NULL) 
    // {
    // 	free(p->key);
    // 	free(p->valuer);
    // 	free(p);
    // }
}

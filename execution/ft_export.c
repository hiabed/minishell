/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 16:40:11 by mkatfi            #+#    #+#             */
/*   Updated: 2023/07/18 22:49:15 by mhassani         ###   ########.fr       */
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

void to_be_contined(int i, t_env **p, char **s)
{
    char** a;
    char* valuer;
    
    a = key_valu(s[i]);
    if (is_he_in_env(*p, a[0]) == 1)
    {
        valuer = valuer_of_key(*p, a[0]);
        char* val = ft_strjoin(valuer, a[1]);
        if (icale(s[i]) == 2)
            riblce_v(*p, a[0], val);
        else if (icale(s[i]) == 1)
            riblce_v(*p, a[0], a[1]);
        free(val);
    }
    else if (is_he_in_env(*p, a[0]) == 0)
    {
        if (icale(s[i]) == 1 || icale(s[i]) == 2)
        {
            if(s[0][0] != '=')
                ft_lstadd_back_env(p, ft_lstnew_env(s[i]));
            else
                ft_Error(*s, 1);;
        }
        else if (icale(s[i]) == 0)
        {
            if(s[0][0] != '=')
                ft_lstadd_back_env(p, ft_lstnew_env(s[i]));
            else
                ft_Error(*s, 1);;
            free(a[1]);
            a[1] = NULL;
            riblce_v(*p, a[0], a[1]);
        }
    }
    freepath(a);
}

void ft_export(char **s, t_env **p, int fd)
{
    int i = 0;
    g_g.exit_status = 0;
    if (s == NULL || *s == NULL)
        sort_nb(*p, fd);
    else
    {
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 21:59:36 by mkatfi            #+#    #+#             */
/*   Updated: 2023/07/18 22:28:38 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int is_builtin_command(char* command)
{
    char* builtins[] = {"cd","pwd","echo","exit","export","env","unset"};
    int i = 0;
    while (i < 7)
    {
        if (ft_strcmp(command, builtins[i]) == 0)
            return (1);
        i++;
    }
    return (0);
}

void  chaeck_builtins(t_env** p, t_token* ptr)
{
    if (ptr && ptr->cmd && ptr->arg)
    {
        if (!ft_strcmp(ptr->cmd, "echo"))
            ft_echo(ptr->arg, ptr->out);
        else if (!ft_strcmp(ptr->cmd, "pwd"))
            ft_pwd(1, ptr->out);
        else if (!ft_strcmp(ptr->cmd, "cd"))
            ft_cd(ptr->arg, p);
        else if (!ft_strcmp(ptr->cmd, "env"))
            ft_env(*p, ptr);
        else if (!ft_strcmp(ptr->cmd, "export"))
            ft_export(ptr->arg, p, ptr->out);
        else if (!ft_strcmp(ptr->cmd, "unset"))
            ft_unset(p, ptr->arg);
        else if (!ft_strcmp(ptr->cmd, "exit"))
            ft_exit(ptr->arg);
        else
            return ;
    }
}

void  chaeck_builtins1(t_env** p, t_token* ptr)
{
    if (ptr && ptr->cmd && ptr->arg)
    {
        main_ex(p, ptr);
    }
}
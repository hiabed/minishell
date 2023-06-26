/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkatfi <mkatfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 21:59:36 by mkatfi            #+#    #+#             */
/*   Updated: 2023/06/25 18:33:32 by mkatfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void chaeck_builtins(t_env** p, t_token* ptr)
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
            ft_export(ptr->arg, *p, ptr->out);
        else if (!ft_strcmp(ptr->cmd, "unset"))
            ft_unset(p, ptr->arg);
        else if (!ft_strcmp(ptr->cmd, "exit"))
            ft_exit(ptr->arg);
        else
            main_ex(*p, ptr);
    }
}
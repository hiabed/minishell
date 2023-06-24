/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 21:59:36 by mkatfi            #+#    #+#             */
/*   Updated: 2023/06/22 20:42:13 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// int chaeck_what_doyou_main(char* d, char** s)
// {
      
// }
void chaeck_builtins(t_env* p, t_token* ptr)
{
    if (ptr && ptr->cmd && ptr->arg)
    {
        if (!ft_strcmp(ptr->cmd, "echo"))
            ft_echo(ptr->arg, 1);
        else if (!ft_strcmp(ptr->cmd, "pwd"))
            ft_pwd(1);
        else if (!ft_strcmp(ptr->cmd, "cd"))
            ft_cd(ptr->arg, &p);
        else if (!ft_strcmp(ptr->cmd, "env"))
            ft_env(p);
        else if (!ft_strcmp(ptr->cmd, "export"))
            ft_export(ptr->arg, p);
        else if (!ft_strcmp(ptr->cmd, "unset"))
            ft_unset(&p, ptr->arg);
        else if (!ft_strcmp(ptr->cmd, "exit"))
            ft_exit(ptr->arg);
        // else
        // 	write(2, "commnd not fond\n", 17);
        else
            main_ex(p, ptr);
    }
}
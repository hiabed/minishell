	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkatfi <mkatfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 20:12:43 by mkatfi            #+#    #+#             */
/*   Updated: 2023/06/23 18:54:51 by mkatfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	freepath(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

void first_cmd(t_env* p, t_token* ptr, int* pip)
{
    char* path = NULL;
    char** cmd = NULL;
    char** ev = NULL;
    int id = fork();
    
    if (id == 0)
    {
        if (ptr->fd > 0)
            dup2(ptr->fd, 0);
        if (ptr->out == 1 && ptr->next)
            dup2(pip[1], 1);
        else
            dup2(ptr->out, 1);
        close(pip[0]);
        path = get_path_cmd(p, ptr->cmd, ptr->arg);
        cmd = join_cmd(ptr->cmd, ptr->arg);
        ev = get_envrment(p);
        if (path == NULL)
        {
            perror("commd not fond");
            exit(127);
        }
        execve(path, cmd, ev);
        perror("execve");
		exit(1);
    }
    // free(path);
    free(cmd);
    free(ev);
}

void any_next_cmd(t_env* p, t_token* ptr, int last_fd, int *pipe_2)
{
    char* path = NULL;
    char** cmd = NULL;
    char** ev = NULL;
    int id = fork();
    if (id == 0)
    {
        if (ptr->fd > 0)
            dup2(ptr->fd, 0);
        else 
            dup2(last_fd, 0);
        if (ptr->out == 1 && ptr->next)
            dup2(pipe_2[1], 1);
        else
            dup2(ptr->out, 1);
        close(pipe_2[0]);
        close(pipe_2[1]);
        close(last_fd);
        path = get_path_cmd(p, ptr->cmd, ptr->arg);
        cmd = join_cmd(ptr->cmd, ptr->arg);
        ev = get_envrment(p);
        if (path == NULL)
        {
            perror("commd not fond");
            exit(127);
        }
        execve(path, cmd, ev);
        perror("execve: ");
        exit(1);
    }
    // free(path);
     free(cmd);
    free(ev);
}


void main_ex(t_env* p, t_token* ptr)
{
    int last_fd = 0;
    int pip[2];
    
    pipe(pip);
    first_cmd(p, ptr,pip);
    last_fd = pip[0];
    close(pip[1]);
    ptr = ptr->next;
    while (ptr)
    {
        pipe(pip);
        any_next_cmd(p, ptr, last_fd, pip);
        close(last_fd);
        last_fd = pip[0];
        close(pip[1]);
        ptr = ptr->next;
    }
    while (wait(NULL) != -1)
		;
}

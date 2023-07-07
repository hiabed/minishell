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

void    cmd_signal(int sigint)
{
    (void)sigint;
    write(1, "\n", 1);
}

int	ft_lstsize_1(t_token *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
void	freepath(char** ptr)
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

int first_cmd(t_env* p, t_token* ptr, int* pip)
 {
    int id = fork();
    char* path;
    char** cmd;
    char** ev;
    if (id == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        if (ptr->fd > 0)
            dup2(ptr->fd, 0);
        if (ptr->out == 1 && ptr->next) 
            dup2(pip[1], 1);
        else 
            dup2(ptr->out, 1);
        close(pip[0]);
        if (is_builtin_command(ptr->cmd))
        {
            chaeck_builtins(&p,  ptr);
            exit(0);
        }
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
    return id;
}

int any_next_cmd(t_env* p, t_token* ptr, int last_fd, int *pipe_2)
{
    int id = fork();
    char* path;
    char** cmd;
    char** ev;
    if (id == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
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
        if (is_builtin_command(ptr->cmd))
        {
            chaeck_builtins(&p, ptr);
            exit(0);
        }
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
    return id;
}

void main_ex(t_env** p, t_token* ptr)
{
    int status;
    int last_fd = 0;
    int pip[2];
    int pid =0;
    pipe(pip);
    if (ft_lstsize_1(ptr) == 1 && is_builtin_command(ptr->cmd))
    {
        chaeck_builtins(p, ptr);
        return ;
    }
    else
        pid = first_cmd(*p, ptr, pip);
    last_fd = pip[0];
    close(pip[1]);
    ptr = ptr->next;
    while (ptr)
    {
        pipe(pip);
        pid = any_next_cmd(*p, ptr, last_fd, pip);
        close(last_fd);
        last_fd = pip[0];
        close(pip[1]);
        ptr = ptr->next;
    }
    signal(SIGINT, cmd_signal);
    waitpid(pid, &status, 0);
    while (wait(NULL) != -1)
        ;
    if (WIFSIGNALED(status))
    {
        if(WTERMSIG(status) == 3)
        {
            write(1, "^\\Quit: 3\n", 10);
        }
    }
    signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

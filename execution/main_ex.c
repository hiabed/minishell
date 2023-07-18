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

    t_token *data = ptr;
    if (id == 0)
    {
        if(data->fd == -1)
            exit(0);
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        if (data->fd > 0)
            dup2(data->fd, 0);
        if (data->out == 1 && data->next) 
            dup2(pip[1], 1);
        else 
            dup2(data->out, 1);
        close(pip[0]);
        if (is_builtin_command(data->cmd))
        {
            chaeck_builtins(&p,  data);
            g_g.exit_status = 0;
            exit(g_g.exit_status);
        }
        path = get_path_cmd(p, data->cmd, data->arg);
        cmd = join_cmd(data->cmd, data->arg);
        if (cmd[0][0] == '/' && (cmd[0][1] == '/' || cmd[0][1] == ' ' || cmd[0][1] == '\0'))
        {
            ft_Error(data->cmd, 7);
            g_g.exit_status = 126;
            exit(g_g.exit_status);
        }
        ev = get_envrment(p);
        if (path == NULL || data->cmd[0] == '\0')
        {
            if(data->cmd[0] == '/')
                ft_Error(data->cmd,5);
            else
                ft_Error(data->cmd,6);
            g_g.exit_status = 127;
            exit(g_g.exit_status);
        }
        execve(path, cmd, ev);
        perror("execve");
        g_g.exit_status = 1;
        exit(g_g.exit_status);
    }
    return id;
}

int any_next_cmd(t_env* p, t_token* ptr, int last_fd, int *pipe_2)
{
    int id = fork();
    char* path;
    char** cmd;
    char** ev;
    t_token *data = ptr;
    if (id == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        path = get_path_cmd(p, data->cmd, data->arg);
        cmd = join_cmd(data->cmd, data->arg);
        ev = get_envrment(p);
        if (data->fd > 0)
            dup2(data->fd, 0);
        else
            dup2(last_fd, 0);
        if (data->out == 1 && data->next)
            dup2(pipe_2[1], 1);
        else
            dup2(data->out, 1);
        close(pipe_2[0]);
        close(pipe_2[1]);
        close(last_fd);
        if (is_builtin_command(data->cmd))
        {
            chaeck_builtins(&p, data);
            g_g.exit_status = 0;
            exit(g_g.exit_status);
        }
        else if (path == NULL  || data->cmd[0] == '\0')
        {
            ft_Error(data->cmd,3);
            g_g.exit_status = 127;
            exit(g_g.exit_status);
        }
        execve(path, cmd, ev);
        perror("execve: ");
        g_g.exit_status = 1;
        exit(g_g.exit_status);
    }
    return id;
}

void main_ex(t_env** p, t_token* ptr)
{
    int status;
    int last_fd = 0;
    int pip[2];
    int pid = 0;
    t_token *data = ptr;
    pipe(pip);
    if (ft_lstsize_1(data) == 1 && is_builtin_command(data->cmd))
    {
        chaeck_builtins(p, data);
        return ;
    }
    else
        pid = first_cmd(*p, data, pip);
    last_fd = pip[0];
    close(pip[1]);
    data = data->next;
    while (data)
    {
        pipe(pip);
        pid = any_next_cmd(*p, data, last_fd, pip);
        close(last_fd);
        last_fd = pip[0];
        close(pip[1]);
        data = data->next;
    }
    signal(SIGINT, cmd_signal);
    waitpid(pid, &status, 0);
    while (wait(NULL) != -1)
        ;
    if (WIFSIGNALED(status))
    {
        if(WTERMSIG(status) == 3)
        {
            write(1, "Quit: 3\n", 8);
            g_g.exit_status = 131;
        }
        else if (WTERMSIG(status) == 2)
            g_g.exit_status = 130;
    }
    else
        g_g.exit_status =  WEXITSTATUS(status);
    signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

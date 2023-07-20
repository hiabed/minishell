/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 20:12:43 by mkatfi            #+#    #+#             */
/*   Updated: 2023/07/19 16:02:51 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	first_cmd(t_env *p, t_token *ptr, int *pip)
{
	g_g.id = fork();
	g_g.dataa = ptr;
	if (g_g.id == 0)
	{
		if (g_g.dataa->fd == -1 || g_g.dataa->out == -1)
			exit(0);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (g_g.dataa->fd > 0)
			dup2(g_g.dataa->fd, 0);
		if (g_g.dataa->out == 1 && g_g.dataa->next)
			dup2(pip[1], 1);
		else
			dup2(g_g.dataa->out, 1);
		close(pip[0]);
		if (is_builtin_command(g_g.dataa->cmd))
		{
			chaeck_builtins(&p, g_g.dataa);
			g_g.exit_status = 0;
			exit(g_g.exit_status);
		}
		first_cmd_shorter(p, g_g.dataa);
	}
	return (g_g.id);
}

int	any_next_cmd(t_env *p, t_token *ptr, int last_fd, int *pipe_2)
{
	int		id;
	t_token	*data;

	id = fork();
	data = ptr;
	if (id == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (g_g.dataa->fd == -1 || g_g.dataa->out == -1)
			exit(0);
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
		any_next_cmd_shorter(p, data);
	}
	return (id);
}

void	main_ex(t_env **p, t_token *ptr)
{
	int	status;
	int	pid;

	pid = 0;
	main_ex_shorter(p, ptr);
	signal(SIGINT, cmd_signal);
	waitpid(pid, &status, 0);
	while (wait(NULL) != -1)
		;
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 3)
		{
			write(1, "Quit: 3\n", 8);
			g_g.exit_status = 131;
		}
		else if (WTERMSIG(status) == 2)
			g_g.exit_status = 130;
	}
	else
		g_g.exit_status = WEXITSTATUS(status);
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ex_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:55:39 by mhassani          #+#    #+#             */
/*   Updated: 2023/07/19 23:50:43 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	main_ex_shorter(t_env **p, t_token *ptr)
{
	t_token	*data;

	g_g.last_fd = 0;
	g_g.pid = 0;
	data = ptr;
	pipe(g_g.pip);
	if (ft_lstsize_1(data) == 1 && is_builtin_command(data->cmd))
	{
		chaeck_builtins(p, data);
		return ;
	}
	else
		g_g.pid = first_cmd(*p, data, g_g.pip);
	g_g.last_fd = g_g.pip[0];
	close(g_g.pip[1]);
	data = data->next;
	while (data)
	{
		pipe(g_g.pip);
		g_g.pid = any_next_cmd(*p, data, g_g.last_fd, g_g.pip);
		close(g_g.last_fd);
		g_g.last_fd = g_g.pip[0];
		close(g_g.pip[1]);
		data = data->next;
	}
}

void	any_next_cmd_shorter(t_env *p, t_token *data)
{
	char	*path;
	char	**cmd;
	char	**ev;

	path = get_path_cmd(p, data->cmd, data->arg);
	cmd = join_cmd(data->cmd, data->arg);
	ev = get_envrment(p);
	if (is_builtin_command(data->cmd))
	{
		chaeck_builtins(&p, data);
		g_g.exit_status = 0;
		exit(g_g.exit_status);
	}
	else if (path == NULL || data->cmd[0] == '\0')
	{
		ft_error(data->cmd, 3);
		g_g.exit_status = 127;
		exit(g_g.exit_status);
	}
	execve(path, cmd, ev);
	perror("execve: ");
	g_g.exit_status = 1;
	exit(g_g.exit_status);
}

void	first_cmd_shorter2(t_token *data)
{
	g_g.y = 0;
	while (g_g.cmdd[0][g_g.y] && g_g.cmdd[0][g_g.y] == '/')
	{
		if (ft_isalnum(g_g.cmdd[0][g_g.y]))
		{
			ft_error_2(data->cmd, 6);
			g_g.exit_status = 127;
			exit(g_g.exit_status);
		}
		g_g.y++;
	}
	if (!g_g.cmdd[0][g_g.y])
	{
		ft_error_2(data->cmd, 7);
		g_g.exit_status = 126;
		exit(g_g.exit_status);
	}
	if ((g_g.cmdd[0][0] == '.' && g_g.cmdd[0][1] == '/')
		|| g_g.cmdd[0][0] == '/')
	{
		ft_error_2(data->cmd, 5);
		g_g.exit_status = 127;
		exit(g_g.exit_status);
	}
}

void	first_cmd_shorter(t_env *p, t_token *data)
{
	char	**ev;

	g_g.path = get_path_cmd(p, data->cmd, data->arg);
	g_g.cmdd = join_cmd(data->cmd, data->arg);
	ev = get_envrment(p);
	first_cmd_shorter2(data);
	if (g_g.path == NULL || data->cmd[0] == '\0')
	{
		if (data->cmd[0] == '/')
			ft_error_2(data->cmd, 5);
		else
			ft_error_2(data->cmd, 6);
		g_g.exit_status = 127;
		exit(g_g.exit_status);
	}
	execve(g_g.path, g_g.cmdd, ev);
	perror("execve");
	g_g.exit_status = 1;
	exit(g_g.exit_status);
}

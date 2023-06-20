/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 23:32:42 by mhassani          #+#    #+#             */
/*   Updated: 2023/06/20 18:02:46 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc(t_token *p)
{
	char	*line;
	int		pipefd[2];

	pipe(pipefd);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("exit\n");
			exit(EXIT_FAILURE);
		}
		if (!(ft_strcmp(p->red->limiter, line)))
			break ;
		ft_putstr_fd(line, pipefd[1]);
		free(line);
	}
	free(line);
	close(pipefd[1]);
	return (pipefd[0]);
}

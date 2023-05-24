/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:52:55 by mhassani          #+#    #+#             */
/*   Updated: 2023/05/24 21:36:48 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "./libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_data
{
	int	i;
	int	error;
	int cote_in_dcotes;
	int dcotes_in_cote;
} t_data;

void	pipe_syntax_errors(char *cmd, t_data *data);
void	red_syntax_errors(char *cmd, t_data *data);
void	cotes_syntax_errors(char *cmd, t_data *data);
void	syntax_errors(char *cmd, t_data *data);

#endif
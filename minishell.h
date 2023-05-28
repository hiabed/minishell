/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:52:55 by mhassani          #+#    #+#             */
/*   Updated: 2023/05/28 22:54:54 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_data
{
	int						i;
	int						error;
	int						cote_in_dcotes;
	int						dcotes_in_cote;
}							t_data;

typedef struct s_redirection
{
	struct s_redirection	*next;
	int						red;
	char					*file;
	char					*limiter;
}							t_redirection;

typedef struct s_token
{
	struct s_token			*next;
	char					**token;
	char					*cmd;
	char					**arg;
}							t_token;

void						pipe_syntax_errors(char *cmd, t_data *data);
void						red_syntax_errors(char *cmd, t_data *data);
void						cotes_syntax_errors(char *cmd, t_data *data);
void						syntax_errors(char *cmd, t_data *data);
void						replace_pipe_in_quotes(char *cmd);
char						**split_with_pipe(char *cmd);
void						replace_space_in_quotes(char *cmd);
char						**split_with_space(char *token);
void						replace_red(char *cmd);

#endif
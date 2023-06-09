/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:52:55 by mhassani          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/06/09 16:42:11 by mhassani         ###   ########.fr       */
=======
/*   Updated: 2023/06/08 22:06:15 by mhassani         ###   ########.fr       */
>>>>>>> e316377081825232a8b738fc065a9ab888e0e55e
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
	int						flag;
	int						*c_args;
	int						cote_in_dcotes;
	int						dcotes_in_cote;
}							t_data;

typedef struct s_redirection
{
	struct s_redirection	*next;
	int						type;
	char					*file;
	char					*limiter;
}							t_redirection;

typedef struct s_token
{
	t_redirection			*red;
	char					*cmd;
	char					**arg;
	struct s_token			*next;
}							t_token;

void						pipe_syntax_errors(char *cmd, t_data *data);
void						red_syntax_errors(char *cmd, t_data *data);
void						cotes_syntax_errors(char *cmd, t_data *data);
void						syntax_errors(char *cmd, t_data *data);
void						replace_pipe_in_quotes(char *cmd);
char						**split_with_pipe(char *cmd);
void						replace_space_in_quotes(char *token);
char						**split_with_space(char *token);
void						replace_red_in_quotes(char *cmd);
void						bring_back(char *cmd);
int							count_args(char **words);
char						**ft_arg(char **words);
char						*ft_cmd(char **words);
t_token						*ft_lstnew_token(char **words);
void						ft_lstadd_token(t_token **lst, t_token *new);
void	ft_lstadd_red(t_redirection **lst,
					t_redirection *new);
char						*ft_file_name(char *words, int type);
char						*ft_limiter_name(char *words, int type);
int							ft_number_type(char *words);
t_redirection				*ft_lstnew_red(char **words);
t_redirection				*ft_redirections(char **words);
int							count_strings(char *words);
int							word_len(char *words);
char						**strings_without_quotes(char *words);
char						*join_empty_strings(char *words);

#endif
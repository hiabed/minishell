/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 19:52:02 by mhassani          #+#    #+#             */
/*   Updated: 2023/06/18 17:29:01 by mhassani         ###   ########.fr       */
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

typedef struct g
{
	int exit_status;
	int i;
}							g_var;

g_var						*g;

int							exit_status;

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
t_token						*ft_lstnew_token(char **words, char **envp);
void						ft_lstadd_token(t_token **lst, t_token *new);
void	ft_lstadd_red(t_redirection **lst,
					t_redirection *new);
char						*ft_file_name(char *words, char **envp, int type);
char						*ft_limiter_name(char *words, int type);
int							ft_number_type(char *words);
t_redirection				*ft_lstnew_red(char **words, char **envp);
t_redirection				*ft_redirections(char **words, char **envp);
int							count_strings(char *words);
int							word_len(char *words);
char						**strings_without_quotes(char *words, char **envp);
char						*join_strings_to_be_one(char *words, char **envp);
char						*space_arround_red(char *s1);
void						ft_fill_ptr(char *s1, char *ptr, int i, int j);
int							cmd_lenght(char *s);
char						*env_key(char *envp);
char						*env_value(char *envp, char *no_quotes);
char						*ft_expand_value(char *no_quotes, char **envp);
int							before_dollar_len(char *no_quotes);
int							ft_strcmp(char *s1, char *s2);
char						*print_not_expanded_dollars(char *no_quotes);
char						*after_expand(char *no_quotes);
char						*print_expanded_dollars(char *no_quotes);
int							num_dollars(char *no_quotes);
char						**heredoc_without_quotes(char *words);
char						*join_heredoc_to_be_one(char *words);
char						*fill_expand(char *no_quotes_str, char **envp);
void						print_info_without_quotes(t_token *ptr,
								char **envp);

#endif
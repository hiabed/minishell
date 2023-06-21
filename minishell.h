/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 19:52:02 by mhassani          #+#    #+#             */
/*   Updated: 2023/06/21 17:52:51 by mhassani         ###   ########.fr       */
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
	char **str;
	int exit_status;
	int i;
	int j;
	int k;
}							g_var;

g_var						g;

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

typedef struct s_expand
{
	char					**envp;
	char					*no_q;
	char					*chars;
	char					*temp;
	int						i;
	int						j;
	int						k;
	int						len;
}							t_expand;

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
	int						fd;
	int						out;
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
char						**strings_without_quotes(char *words, char **envp);
char						*join_strings_to_be_one(char *words, char **envp);
char						*space_arround_red(char *s1);
void						ft_fill_ptr(char *s1, char *ptr, int i, int j);
int							cmd_lenght(char *s);
char						*env_key(char *envp);
char						*env_value(char *envp);
char						*ft_expand_value(char *no_quotes, char **envp);
int							before_dollar_len(char *no_quotes);
int							ft_strcmp(char *s1, char *s2);
char						*print_not_expanded_dollars(char *no_quotes);
char						*after_expand(char *no_quotes);
int							after_expand_check(char *no_quotes);
char						*print_expanded_dollars(char *no_quotes);
int							num_dollars(char *no_quotes);
char						**heredoc_without_quotes(char *words);
char						*join_heredoc_to_be_one(char *words);
char						*fill_expand(char *str, char **envp);
void	infos_without_quotes(t_token *ptr,
							char **envp);
void						print_data(t_token *ptr);
void						skip_d_quotes(char *words, int *i, int *count);
void						skip_s_quotes(char *words, int *i, int *count);
int							count_strings(char *words);
int							word_len(char *words);
int							word_len_single(char *words);
int							len(char *words);
int							here_doc(t_token *p);
char						*fst_chars(char *no_quotes, int i);
char						*only_dollar(char *no_q, char *temp);
char						*empty_string(char *str, int *i);
char						*fill_word_without_quotes(char *str, char *words,
								int *i);
char						*fill_word_with_d_quotes(char *str, char *words,
								int *i);
char						*fill_word_with_s_quotes(char *str, char *words,
								int *i);
char						*fill_expand(char *str, char **envp);
int							empty_string_condition(char *words, int *i);
void						p_in_double_quotes(char *cmd);
void						s_in_double_quotes(char *token);
void						increment_i(char *cmd, int *i);
void						redirections(t_token *ptr);

#endif
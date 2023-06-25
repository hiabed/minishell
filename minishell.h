/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 19:52:02 by mhassani          #+#    #+#             */
/*   Updated: 2023/06/23 23:57:34 by mhassani         ###   ########.fr       */
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
	int						fd;
	int						out;
	char					*cmd;
	char					**arg;
	struct s_token			*next;
}							t_token;

typedef struct s_glob
{
	char					*value;
	char					*result;
	char					**str;
	char					*cmd;
	char					*dollars;
	char					*chars;
	char					*command;
	char					**tokens;
	char					**words;
	t_data					*data;
	t_token					*ptr;
	int						exit_status;
	int						i;
	int						j;
	int						k;
	int						count;
	int						pipefd;
	int						pipe_2;
}							t_glob;

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

typedef struct s_env
{
	char					*key;
	char					*valuer;
	char					*content;
	int						index;
	struct s_env			*next;
}							t_env;

t_glob						g_g;

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
t_token						*ft_lstnew_token(char **words, t_env *envp);
void						ft_lstadd_token(t_token **lst, t_token *new);
void	ft_lstadd_red(t_redirection **lst,
					t_redirection *new);
char						*ft_file_name(char *words, t_env *envp, int type);
char						*ft_limiter_name(char *words, int type);
int							ft_number_type(char *words);
t_redirection				*ft_lstnew_red(char **words, t_env *envp);
t_redirection				*ft_redirections(char **words, t_env *envp);
char						**strings_without_quotes(char *words, t_env *envp);
char						*join_strings_to_be_one(char *words, t_env *envp);
char						*space_arround_red(char *s1);
void						ft_fill_ptr(char *s1, char *ptr, int i, int j);
int							cmd_lenght(char *s);
char						*env_value(t_env *a, char *s);
// char						*ft_expand_value(char *no_quotes, t_env *envp);
int							before_dollar_len(char *no_quotes);
int							ft_strcmp(char *s1, char *s2);
char						*print_not_expanded_dollars(char *no_quotes);
char						*after_expand(char *no_quotes);
int							after_expand_check(char *no_quotes);
char						*print_expanded_dollars(char *no_quotes);
int							num_dollars(char *no_quotes);
char						**heredoc_without_quotes(char *words);
char						*join_heredoc_to_be_one(char *words);
char						*fill_expand(char *str, t_env *envp);
void	infos_without_quotes(t_token *ptr,
							t_env *envp);
void						print_data(t_token *ptr);
void						skip_d_quotes(char *words, int *i, int *count);
void						skip_s_quotes(char *words, int *i, int *count);
int							count_strings(char *words);
int							word_len(char *words);
int							word_len_single(char *words);
int							len(char *words);
int							here_doc(t_token *p, t_env *envp); //here;
char						*fst_chars(char *no_quotes, int i);
char						*only_dollar(char *no_q);
char						*empty_string(char *str, int *i);
char						*fill_word_without_q(char *str, char *words,
								int *i);
char						*fill_word_with_d_q(char *str, char *words, int *i);
char						*fill_word_with_s_q(char *str, char *words, int *i);
char						*fill_expand(char *str, t_env *envp);
int							empty_string_condition(char *words, int *i);
void						p_in_double_quotes(char *cmd);
void						s_in_double_quotes(char *token);
void						increment_i(char *cmd, int *i);
char						*ft_expand_value(char *no_q, t_env *envp); //here
void						redirections(t_token *ptr, t_env *envp);   //here;
void						d_quotes_errors(int *dcotes, int *cotes, int *i,
								char *cmd);
void						s_quotes_errors(int *dcotes, int *cotes, int *i,
								char *cmd);
void						outfile_errors(char *cmd, int *i, t_data *data);
void						skip_db_quotes(int *i, char *cmd);
void						skip_sin_quotes(int *i, char *cmd);
char						*ft_expand_value_here_doc(char *no_q, t_env *envp); //here
char						**ft_expand_value_export(char *no_q, t_env *envp); //here
// excution
int							ft_size_n(char *s);
void						ft_lstadd_back_env(t_env **lst, t_env *new);
t_env						*ft_lstnew_env(char *content);
void						ft_echo(char **cmd, int fd);
void						ft_env(t_env *p);
char						*ft_pwd(int k);
void						ft_cd(char **s, t_env **p);
void						ft_export(char **str, t_env *p);
void						ft_env(t_env *p);
char						**key_valu(char *s);
void						ft_unset(t_env **p, char **s);
int							icale(char *s);
void						ft_exit(char **s);
int							cheack_arg(char *s);
char						*str_join(char *s1, char *s2);
int							is_he_in_env(t_env *a, char *s);
void						riblce_v(t_env *a, char *s, char *c);
void						ft_Error(char *s);
void						sort_nb(t_env *a);
void						main_ex(t_env *p, t_token *ptr);
void						chaeck_builtins(t_env *p, t_token *ptr);
int							is_he_in_env(t_env *a, char *s);

#endif
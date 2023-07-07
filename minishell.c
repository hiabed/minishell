/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:53:19 by mhassani          #+#    #+#             */
/*   Updated: 2023/07/07 17:21:00 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**strings_without_quotes(char *words, t_env *envp)
{
	int	i;

	// printf("words: %s\n", words);
	g_g.str = malloc((count_strings(words) + 1) * sizeof(char *));
	g_g.k = 0;
	i = 0;
	while (words[i])
	{
		if (empty_string_condition(words, &i))
			g_g.str[g_g.k] = empty_string(g_g.str[g_g.k], &i);
		else if ((words[i] == '\"' && words[i + 1] != '\"'))
		{
			g_g.str[g_g.k] = fill_word_with_d_q(g_g.str[g_g.k], words, &i);
			g_g.str[g_g.k] = fill_expand(g_g.str[g_g.k], envp);
		}
		else if ((words[i] == '\'' && words[i + 1] != '\''))
			g_g.str[g_g.k] = fill_word_with_s_q(g_g.str[g_g.k], words, &i);
		else if (words[i] != '\"' && words[i] != '\'')
		{
			g_g.str[g_g.k] = fill_word_without_q(g_g.str[g_g.k], words, &i);
			g_g.str[g_g.k] = fill_expand(g_g.str[g_g.k], envp);
		}
		g_g.k++;
	}
	g_g.str[g_g.k] = NULL;
	return (g_g.str);
}

char	*join_strings_to_be_one(char *words, t_env *envp)
{
	int		i;
	char	*joined_string;
	char	**to_be_joined;
	char	*temp;

	i = 0;
	joined_string = words;
	to_be_joined = strings_without_quotes(words, envp);
	if (to_be_joined[i])
	{
		joined_string = to_be_joined[i];
		while (to_be_joined[i + 1])
		{
			temp = ft_strjoin(joined_string, to_be_joined[i + 1]);
			joined_string = temp;
			i++;
		}
	}
	return (joined_string);
}

char	*join_heredoc_to_be_one(char *words)
{
	int		i;
	char	*joined_string;
	char	**to_be_joined;
	char	*temp;

	i = 0;
	joined_string = words;
	to_be_joined = heredoc_without_quotes(words);
	if (to_be_joined[i])
	{
		joined_string = to_be_joined[i];
		while (to_be_joined[i + 1])
		{
			temp = ft_strjoin(joined_string, to_be_joined[i + 1]);
			joined_string = temp;
			i++;
		}
	}
	return (joined_string);
}

void	minishell(t_data *data, char *cmd, t_env *envp)
{
	data->error = 0;
	data->flag = 0;
	syntax_errors(cmd, data);
	if (!data->error)
	{
		g_g.command = space_arround_red(cmd);
		replace_pipe_in_quotes(g_g.command);
		g_g.tokens = split_with_pipe(g_g.command);
		g_g.l = 0;
		g_g.expand = 0;
		g_g.ptr = NULL;
		while (g_g.tokens[g_g.l])
		{
			if (g_g.tokens[g_g.l][0] == '$')
			{
				g_g.tokens[g_g.l] = ft_expand_value(g_g.tokens[g_g.l], envp);
				g_g.expand = 1;
			}
			replace_space_in_quotes(g_g.tokens[g_g.l]);
			g_g.words = split_with_space(g_g.tokens[g_g.l]);
			ft_lstadd_token(&g_g.ptr, ft_lstnew_token(g_g.words, envp));
			g_g.l++;
		}
		infos_without_quotes(g_g.ptr, envp);
		print_data(g_g.ptr);
	}
}

void	ctrl_c(int sigint)
{
    write(1, "\n", 1);
	(void)sigint;
    rl_on_new_line(); // Move to a new line
    rl_replace_line("", 0); // Clear the current input line
    rl_redisplay(); // Redisplay the prompt
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;
	int		h;

	ac = 0;
	av = NULL;
	g_g.data = malloc(sizeof(t_data));
	env = NULL;
	h = 0;
	while (envp[h])
	{
		ft_lstadd_back_env(&env, ft_lstnew_env(envp[h]));
		h++;
	}
	if (!g_g.data)
		return (0);
	g_g.exit_status = 1;
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		g_g.cmd = readline("minishell-3.2$ ");
		if (!g_g.cmd)
		{
			write(1, "exit\n", 5);
			exit(EXIT_FAILURE);
		}
		if(ft_strlen(g_g.cmd) > 0)
			add_history(g_g.cmd);
		minishell(g_g.data, g_g.cmd, env);
		chaeck_builtins1(&env, g_g.ptr);
	}
	// system("leaks minishell");
	// exit(1);
	free(g_g.cmd);
	free(g_g.command);
	return (0);
}

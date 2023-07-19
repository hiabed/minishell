/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:17:01 by mhassani          #+#    #+#             */
/*   Updated: 2023/07/19 17:42:42 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_expand_case(t_env *envp)
{
	char	*token;

	if (g_g.tokens[g_g.l][0] == '$')
	{
		token = g_g.tokens[g_g.l];
		g_g.tokens[g_g.l] = ft_expand_value(g_g.tokens[g_g.l], envp);
		g_g.expand = 1;
		free(token);
	}
}

void	ft_free_data(t_token **leaks)
{
	t_token			*b;
	t_redirection	*a;

	while ((*leaks))
	{
		b = (*leaks);
		while ((*leaks)->red)
		{
			a = (*leaks)->red;
			if (g_g.signal_check == 0)
				free(a->file);
			free(a->limiter);
			(*leaks)->red = (*leaks)->red->next;
			free(a);
		}
		free((*leaks)->cmd);
		freepath((*leaks)->arg);
		(*leaks) = ((*leaks))->next;
		free(b);
	}
}

char	*join_heredoc_to_be_one(char *words)
{
	int		i;
	char	*joined_string;
	char	**to_be_joined;
	char	*temp;
	char	*x;

	i = 0;
	joined_string = words;
	to_be_joined = heredoc_without_quotes(words);
	if (to_be_joined[i])
	{
		joined_string = to_be_joined[i];
		while (to_be_joined[i + 1])
		{
			x = joined_string;
			temp = ft_strjoin(joined_string, to_be_joined[i + 1]);
			joined_string = temp;
			free(x);
			i++;
		}
	}
	return (joined_string);
}

void	write_error(void)
{
	write(2,
		"minishell: unexpected EOF while looking for matching `\"'\n",
		57);
	write(2, "minishell: syntax error: unexpected end of file\n", 48);
}

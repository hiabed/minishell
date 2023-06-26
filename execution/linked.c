/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkatfi <mkatfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:41:33 by mkatfi            #+#    #+#             */
/*   Updated: 2023/06/25 18:59:19 by mkatfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void continue_key_valu(char **g, char *s)
{
	int j;
	int k;
	
	j = 0;
	k = 0;
	while (s[j] && s[j] != '=' && s[j] !='+')
		g[0][k++] = s[j++];
	g[0][k] = '\0';
	k = 0;
	if ((s[j] == '+' && s[j + 1] == '='))
	{
		j += 2;
		while (s[j])
			g[1][k++] = s[j++];
		g[1][k] = '\0';
	}	
	if (s[j] == '=')
	{
		j++;
		while (s[j])
			g[1][k++] = s[j++];
	}
	g[1][k] = '\0';
}

char **key_valu(char* s)
{
	int		i;
	char	**g;
	if (!s)
		return(NULL);
	g = malloc(sizeof(char*) * 3);
	if (g == NULL)
		return NULL;
	g[2] = NULL;
	i = 0;
	while (s[i] && s[i] != '=' && s[i] !='+')
		i++;
	g[0] = malloc(i + 1);
	g[1] = malloc(ft_strlen(s) - i + 1);
	continue_key_valu(g, s);
	if (g[0] != NULL || g[1] != NULL)
		return(g);
	// free(g[0]);
	// free(g[1]);
	// free(g);
	return(NULL);
}


t_env* ft_lstnew_env(char* content)
{
	t_env		*head;
	char** s;

	s = key_valu(content);
	head = malloc(sizeof(t_env));
	if (!head)
		return (NULL);
	head->content = ft_strdup(content);
	head->key = ft_strdup(s[0]);
	head->valuer = ft_strdup(s[1]);
	head->index = -1;
	head->next = NULL;
	return (head);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*ptr;

	ptr = *lst;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}


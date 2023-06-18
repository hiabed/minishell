/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_lenghts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 20:44:34 by mhassani          #+#    #+#             */
/*   Updated: 2023/06/18 20:44:55 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	before_dollar_len(char *no_quotes)
{
	int	i;

	i = 0;
	while (no_quotes[i] && no_quotes[i] != '$')
		i++;
	return (i);
}

int	num_dollars(char *no_quotes)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (no_quotes[i] && no_quotes[i] == '$')
	{
		count++;
		i++;
	}
	return (count);
}
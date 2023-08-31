/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   search_token.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/28 11:48:59 by laura         #+#    #+#                 */
/*   Updated: 2023/08/31 14:05:39 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/lexical_analyzer.h"

int	find_size(t_tokens *tokens)
{
	int	count;

	count = 0;
	while (tokens)
	{
		count++;
		tokens = tokens->next;
	}
	return (count);
}

int	count_heredocs(t_tokens *tokens)
{
	int	count_here;

	count_here = 0;
	while (tokens != NULL)
	{
		if (tokens->type == T_SMALLSMALL)
			count_here++;
		tokens = tokens->next;
	}
	return (count_here);
}

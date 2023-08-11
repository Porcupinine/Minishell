/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   search_token.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/28 11:48:59 by laura         #+#    #+#                 */
/*   Updated: 2023/08/11 08:05:58 by laura         ########   odam.nl         */
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

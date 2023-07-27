/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_tolken.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 17:24:07 by laura         #+#    #+#                 */
/*   Updated: 2023/07/17 17:26:04 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../../include/minishell.h"
#include "libft.h"
#include <stdio.h>
#include "../../../include/lexical_analyzer.h"

static t_tokens	*find_last(t_tokens *token)
{
	t_tokens	*temp;

	temp = token;
	if (temp == NULL)
		return (NULL);
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	return (temp);
}

void	add_token(t_tokens **tokens, char *token, t_type type)
{
	t_tokens	*new_token;

	new_token = malloc(sizeof(t_tokens));
	if (new_token == NULL)
		ft_error("Malloc token fail\n");
	new_token->str = token;
	new_token->type = type;
	new_token->next = NULL;
	if (*tokens == NULL)
		*tokens = new_token;
	else
	{
		t_tokens	*last_node;

		last_node = find_last(*tokens);
		last_node->next = new_token;
	}
}

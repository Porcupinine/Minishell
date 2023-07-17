/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_tolkens.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 17:24:02 by laura         #+#    #+#                 */
/*   Updated: 2023/07/17 17:25:19 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/lexical_analyzer.h"
#include <stdio.h>

void	print_tokens(t_tokens *tokens)
{
	while (tokens != NULL)
	{
		printf("%s\n", tokens->str);
		tokens = tokens->next;
	}
}

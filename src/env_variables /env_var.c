/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_var.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 17:26:37 by laura         #+#    #+#                 */
/*   Updated: 2023/07/17 17:26:55 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdlib.h>
#include "../../Lib42/include/libft.h"
#include "../../include/lexical_analyzer.h"

void found_equal(t_tokens *tokens)
{

}

void search_for_equals(t_tokens *tolkens)
{
	while(tolkens)
	{
		if (tolkens->type == T_CHAR)
		{
			if(ft_strchr(tolkens->str, '=') != 0)
				found_equal(tolkens);
		}
		tolkens = tolkens->next;
	}
}

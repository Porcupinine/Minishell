/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_machine.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 17:30:08 by laura         #+#    #+#                 */
/*   Updated: 2023/07/17 17:30:15 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/tolken_list_actions.h"
#include "../../Lib42/include/libft.h"
#include "../../include/lexical_analyzer.h"
#include <stdlib.h>
#include <stdio.h>

void	token_error(t_state_machine *parser)
{
	printf("Syntax error\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_commands2.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/11 07:55:33 by laura         #+#    #+#                 */
/*   Updated: 2023/08/16 14:40:47 by lpraca-l      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include <stdlib.h>
#include "libft.h"
#include "../../../include/lexical_analyzer.h"
#include "../../../include/env_var.h"
#include "../../../include/token_list_actions.h"
#include "../../../include/cmd_list_actions.h"
#include "../../../include/I_want_to_break_free.h"
#include "../../../include/errors.h"

void heredoc(t_tokens **it_token, t_commands **cmd)
{
	char *limiter;

	(*it_token) = (*it_token)->next;
	limiter = ft_strdup((*it_token)->str);

	 //current token is heredoc
	 // next token is sfeword
	 //check for quotes need to be a pair, if they are, we ignore expantions, otherwise we go bunkers
	//free limiter

}
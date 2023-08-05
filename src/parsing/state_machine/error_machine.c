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

#include "../../../include/minishell.h"
#include "../../../include/token_list_actions.h"
#include "libft.h"
#include "../../../include/lexical_analyzer.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include "../../include/lexical_analyzer.h"
#include "../../include/I_want_to_break_free.h"

void	syntax_error(t_tokens **tokens, char c)
{
	//error 258
	printf("Syntax error near unexpected token '%c'\n", c);
//	g_exit_code = 258;
	free_token_list(tokens);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_machine.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 17:30:08 by laura         #+#    #+#                 */
/*   Updated: 2023/08/16 14:40:14 by lpraca-l      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../../../include/utils.h"
#include "libft.h"
#include "../../../include/lexical_analyzer.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include "../../include/lexical_analyzer.h"


extern int	g_exit_code;

void	syntax_error(t_state_machine *parser, char c)
{
	if (c == '\n')
		printf("Syntax error near unexpected token `newline'\n");
	else
		printf("Syntax error near unexpected token '%c'\n", c);
	g_exit_code = 258;
	parser->state = S_ERROR;
	free_token_list(&parser->tokens_list);
	parser->tokens_list = NULL;
	return_prompt();
}

void	syntax_error_parse(t_state_machine *parser, t_data *mini_data)
{
	printf("Syntax error near unexpected token `newline'\n");
	g_exit_code = 258;
	free_token_list(&parser->tokens_list);
	parser->tokens_list = NULL;
	free_cmd_list(&mini_data->commands);
	mini_data->commands = NULL;
	return_prompt();
}

void	unclosed_error(t_state_machine *parser)
{
	char	c;

	if (parser->status == S_DQUOTES)
		c = '"';
	else
		c = '\'';
	printf("Unclosed '%c'\n", c);
	g_exit_code = 258;
	free_token_list(&parser->tokens_list);
	parser->tokens_list = NULL;
	return_prompt();
}

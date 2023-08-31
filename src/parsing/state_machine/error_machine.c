/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_machine.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 17:30:08 by laura         #+#    #+#                 */
/*   Updated: 2023/08/31 14:30:45 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../../../include/utils.h"
#include "libft.h"
#include <stdio.h>

void	syntax_error(t_state_machine *parser, char c)
{
	if (c == '\n')
		write(2, "Syntax error near unexpected token `newline'\n", 45);
	else
	{
		write(2, "Syntax error near unexpected token '", 36);
		write(2, &c, 1);
		write(2, "'\n", 2);
	}
	parser->exit_code = 258;
	parser->state = S_ERROR;
	free_token_list(&parser->tokens_list);
	parser->tokens_list = NULL;
	return_prompt();
}

void	syntax_error_parse(t_state_machine *parser, t_data *mini_data)
{
	write(2, "Syntax error near unexpected token `newline'\n", 45);
	parser->exit_code = 258;
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
	write (2, "Unclosed '", 10);
	write(2, &c, 1);
	write(2, "'\n", 2);
	parser->exit_code = 258;
	free_token_list(&parser->tokens_list);
	parser->tokens_list = NULL;
	return_prompt();
}

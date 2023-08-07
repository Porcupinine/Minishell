/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexe.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 17:28:34 by laura         #+#    #+#                 */
/*   Updated: 2023/07/28 11:58:23 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../../../include/token_list_actions.h"
#include "libft.h"
#include "../../../include/lexical_analyzer.h"
#include <stdlib.h>
#include <stdio.h>
#include "../../../include/cmd_list_actions.h"
#include "../../../include/exec.h"

void	token_start(t_state_machine *parser)
{
	char	c;

	c = parser->cmd[parser->count];
	if (ft_strchr(METACHAR, c) == 0 || ft_strchr(QUOTES, c) != 0)
	{
		parser->state = S_CHAR;
		parser->status = S_WORD;
	}
	else if (c == ' ')
		parser->state = S_WHITESPACE;
	else
		syntax_error(parser, c);
}

void	populate_function_ptrs(void (**functions)(t_state_machine *))
{
	(functions)[S_WHITESPACE] = &token_space_newline;
	(functions)[S_PIPE] = &token_pipe;
	(functions)[S_BIG] = &token_bigger;
	(functions)[S_BIGBIG] = &token_bigbig;
	(functions)[S_SMALL] = &token_smaller;
	(functions)[S_SMALSMAL] = &token_smallsmall;
	(functions)[S_CHAR] = &token_str;
}

void	parse_machine(t_data *mini_data, t_state_machine *parser)
{
	void			(*functions[7])(t_state_machine*);

	populate_function_ptrs(functions);
	parser->count = 0;
	parser->cmd = mini_data->command_line;
	token_start(parser);
	while (mini_data->command_line[parser->count] != '\0' && parser->state != S_ERROR)
	{
		if(parser->state == S_ERROR)
			break ;
		functions[parser->state](parser);
		parser->count++;
	}
	if (parser->status == S_DQUOTES || parser->status == S_SQUOTES)
		unclosed_error(parser);
	if(parser->state != S_ERROR)
		add_token(&parser->tokens_list, \
	ft_substr(parser->cmd, parser->start, parser->len), T_CHAR);
}

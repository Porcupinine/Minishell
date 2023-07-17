/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   meta_machine.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 17:27:23 by laura         #+#    #+#                 */
/*   Updated: 2023/07/17 17:28:25 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/tolken_list_actions.h"
#include "../../Lib42/include/libft.h"
#include "../../include/lexical_analyzer.h"
#include <stdlib.h>
#include <stdio.h>

void	token_pipe(t_state_machine *parser)
{
	char	c;

	c = parser->cmd[parser->count];
	if (c == '|' || c == '<' || c == '>')
		parser->state = S_ERROR;
	else
		add_token(&parser->tokens_list, "|", T_PIPE);
	if (ft_strchr(" |<>\"'", c) == 0)
		found_char(parser);
	if (c == ' ' || c == '\n')
		parser->state = S_WHITESPACE;
}

void	token_bigger(t_state_machine *parser)
{
	char	c;

	c = parser->cmd[parser->count];
	if (c == '|')
		parser->state = S_ERROR;
	else if (c == '>')
	{
		add_token(&parser->tokens_list, ">>", T_BIGBIG);
		parser->state = S_BIGBIG;
	}
	else
	{
		add_token(&parser->tokens_list, ">", T_BIG);
		if (c == '<')
			parser->state = S_SMALL;
		if (ft_strchr(" |<>\"'", c) == 0)
			found_char(parser);
		if (c == ' ' || c == '\n')
			parser->state = S_WHITESPACE;
	}
}

void	token_smaller(t_state_machine *parser)
{
	char	c;

	c = parser->cmd[parser->count];
	if (c == '|')
	{
		add_token(&parser->tokens_list, "<", T_SMALL);
		parser->state = S_PIPE;
	}
	else if (c == '<')
	{
		add_token(&parser->tokens_list, "<<", T_SMALLSMALL);
		parser->state = S_BIGBIG;
	}
	else
	{
		add_token(&parser->tokens_list, "<", T_SMALL);
		if (c == '>')
			parser->state = S_SMALL;
		if (ft_strchr(" |<>\"'", c) == 0)
			found_char(parser);
		if (c == ' ' || c == '\n')
			parser->state = S_WHITESPACE;
	}
}

void	token_bigbig(t_state_machine *parser)
{
	char	c;

	c = parser->cmd[parser->count];
	if (c == '>' || c == '|' || c == '<')
	{
		parser->state = S_ERROR;
	}
	if (ft_strchr(" |<>\"'", c) == 0)
		found_char(parser);
	if (c == ' ' || c == '\n')
		parser->state = S_WHITESPACE;
}

void	token_smallsmall(t_state_machine *parser)
{
	char	c;

	c = parser->cmd[parser->count];
	if (c == '>' || c == '|' || c == '<')
	{
		parser->state = S_ERROR;
	}
	if (ft_strchr(" |<>\"'", c) == 0)
		found_char(parser);
	if (c == ' ' || c == '\n')
		parser->state = S_WHITESPACE;
}

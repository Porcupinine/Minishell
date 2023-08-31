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

#include "../../../include/utils.h"
#include "libft.h"

void	token_pipe(t_state_machine *parser)
{
	char	c;

	c = parser->cmd[parser->count];
	if (c == '|' || c == '<' || c == '>')
		syntax_error(parser, c);
	else
		add_token(&parser->tokens_list, ft_strdup("|"), T_PIPE);
	if (ft_strchr(METACHAR, c) == 0)
		found_char(parser);
	if (c == ' ' || c == '\n')
		parser->state = S_WHITESPACE;
}

void	token_bigger(t_state_machine *parser)
{
	char	c;

	c = parser->cmd[parser->count];
	if (c == '|')
		syntax_error(parser, c);
	else if (c == '>')
	{
		add_token(&parser->tokens_list, ft_strdup(">>"), T_BIGBIG);
		parser->state = S_BIGBIG;
	}
	else if (ft_strchr(QUOTES, parser->cmd[parser->count]) != 0)
		found_quotes(parser);
	else
	{
		add_token(&parser->tokens_list, ft_strdup(">"), T_BIG);
		if (c == '<')
			parser->state = S_SMALL;
		if (ft_strchr(METACHAR, c) == 0)
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
		add_token(&parser->tokens_list, ft_strdup("<"), T_SMALL);
		parser->state = S_PIPE;
	}
	else if (c == '<')
	{
		add_token(&parser->tokens_list, ft_strdup("<<"), T_SMALLSMALL);
		parser->state = S_SMALSMAL;
	}
	else if (ft_strchr(QUOTES, parser->cmd[parser->count]) != 0)
		found_quotes(parser);
	else
	{
		add_token(&parser->tokens_list, ft_strdup("<"), T_SMALL);
		if (c == '>')
			parser->state = S_SMALL;
		if (ft_strchr(METACHAR, c) == 0)
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
		syntax_error(parser, c);
	else if (ft_strchr(QUOTES, parser->cmd[parser->count]) != 0)
		found_quotes(parser);
	else if (ft_strchr(METACHAR, c) == 0)
		found_char(parser);
	else if (c == ' ' || c == '\n')
		parser->state = S_WHITESPACE;
}

void	token_smallsmall(t_state_machine *parser)
{
	char	c;

	c = parser->cmd[parser->count];
	if (c == '>' || c == '|')
		syntax_error(parser, c);
	else if (ft_strchr(METACHAR, c) == 0)
		found_char(parser);
	else if (ft_strchr(QUOTES, parser->cmd[parser->count]) != 0)
		found_quotes(parser);
	else if (c == ' ' || c == '\n')
		parser->state = S_WHITESPACE;
}

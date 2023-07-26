/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   char_machine.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 17:30:22 by laura         #+#    #+#                 */
/*   Updated: 2023/07/17 17:31:04 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../../../include/token_list_actions.h"
#include "libft.h"
#include "../../../include/lexical_analyzer.h"
#include <stdlib.h>

void	found_char(t_state_machine *parser)
{
	if (parser->status != S_WORD && parser->status != S_DQUOTES)
	{
		parser->status = S_WORD;
		parser->start = parser->count;
	}
	else
		parser->len++;
	parser->state = S_CHAR;
}

void found_squote(t_state_machine *parser)
{
	if (parser->status == S_WAITING)
	{
		parser->status = S_SQUOTES;
		parser->len++;
		parser->start = parser->count;
	}
	else if (parser->status == S_SQUOTES)
	{
		parser->len++;
		parser->status = S_WORD;
	}
	else if (parser->status == S_WORD)
	{
		parser->len++;
		parser->status = S_SQUOTES;
	}
	else
		parser->len++;
	parser->state = S_CHAR;
}

void found_dquote(t_state_machine *parser)
{
	if (parser->status == S_WAITING)
	{
		parser->len++;
		parser->status = S_DQUOTES;
		parser->start = parser->count;
	}
	else if (parser->status == S_DQUOTES)
	{
		parser->len++;
		parser->status = S_WORD;
	}
	else if (parser->status == S_WORD)
	{
		parser->len++;
		parser->status = S_DQUOTES;
	}
	else
		parser->len++;
	parser->state = S_CHAR;
}

void found_quotes(t_state_machine *parser)
{
	if (parser->cmd[parser->count] == '\'')
		found_squote(parser);
	else if (parser->cmd[parser->count] == '"')
		found_dquote(parser);
}

void	token_str(t_state_machine *parser)
{
	char	c;

	c = parser->cmd[parser->count];
	if (ft_strchr(METACHAR, c) != 0 && parser->status == S_DQUOTES)
		parser->len++;
	else if (ft_strchr(QUOTES, c) != 0)
		found_quotes(parser);
	else if (ft_strchr(METACHAR, c) == 0)
		parser->len++;
	else
	{
		add_token(&parser->tokens_list, \
		ft_substr(parser->cmd, parser->start, parser->len), T_CHAR);
		parser->len = 0;
		parser->status = S_WAITING;
		if (c == ' ' || c == '\n')
			parser->state = S_WHITESPACE;
		else if (c == '>')
			parser->state = S_BIG;
		else if (c == '<')
			parser->state = S_SMALL;
		else if (c == '|')
			parser->state = S_PIPE;
	}
}

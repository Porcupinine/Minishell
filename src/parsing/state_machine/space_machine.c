/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   space_machine.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 17:27:08 by laura         #+#    #+#                 */
/*   Updated: 2023/08/11 08:01:30 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/utils.h"
#include "libft.h"

void	token_space_newline(t_state_machine *parser)
{
	if (ft_strchr("\"'", parser->cmd[parser->count]) != 0)
		found_quotes(parser);
	else if (ft_strchr(METACHAR, parser->cmd[parser->count]) == 0)
	{
		if (parser->status != S_WORD)
		{
			parser->status = S_WORD;
			parser->start = parser->count;
		}
		parser->len++;
		parser->state = S_CHAR;
	}
	else
	{
		if (parser->cmd[parser->count] == '|')
			parser->state = S_PIPE;
		else if (parser->cmd[parser->count] == '>')
			parser->state = S_BIG;
		else if (parser->cmd[parser->count] == '<')
			parser->state = S_SMALL;
		else if (parser->cmd[parser->count] == ' ')
			parser->len++;
	}
}

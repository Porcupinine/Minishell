/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   space_newline.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 17:27:08 by laura         #+#    #+#                 */
/*   Updated: 2023/07/17 17:27:12 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../../../include/token_list_actions.h"
#include "libft.h"
#include "../../../include/lexical_analyzer.h"
#include <stdlib.h>


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

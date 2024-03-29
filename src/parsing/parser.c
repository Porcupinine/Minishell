/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmaessen <dmaessen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/11 08:01:47 by laura         #+#    #+#                 */
/*   Updated: 2023/09/04 14:15:00 by lpraca-l      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Lib42/include/libft.h"
#include "../../include/lexical_analyzer.h"
#include "../../include/utils.h"
#include <stdio.h>

static void	free_parser(t_state_machine *parser)
{
	free(parser);
	parser = NULL;
}

int	parse(t_data *mini_data)
{
	t_state_machine	*parser;

	parser = ft_calloc_exit(1, sizeof (t_state_machine));
	if (parse_machine(mini_data, parser) == 1)
	{
		mini_data->exit_code = parser->exit_code;
		free_parser(parser);
		return (1);
	}
	if (parse_tokens(parser, mini_data) == 1)
	{
		free_parser(parser);
		return (1);
	}
	free_parser(parser);
	return (0);
}

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

static void	free_parser(t_data *mini_data, t_state_machine *parser)
{
	free(mini_data->command_line);
	mini_data->command_line = NULL;
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
		free_parser(mini_data, parser);
		return (1);
	}
	print_tokens(parser->tokens_list);
	if (parse_tokens(parser, mini_data) == 1)
	{
		free_parser(mini_data, parser);
		return (1);
	}
	print_cmd_list(mini_data->commands);
	free_parser(mini_data, parser);
	return (0);
}

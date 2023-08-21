/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/11 08:01:47 by laura         #+#    #+#                 */
/*   Updated: 2023/08/16 14:38:40 by lpraca-l      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Lib42/include/libft.h"
#include "../../include/lexical_analyzer.h"
#include "../../include/token_list_actions.h"
#include "../../include/cmd_list_actions.h"
#include <stdio.h>

void	parse(t_data *mini_data)
{
	t_state_machine	*parser;

	parser = ft_calloc(1, sizeof (t_state_machine));
	if (parser == NULL)
		ft_error("Malloc fail\n");
	parse_machine(mini_data, parser);
//	printf("------TOKEN LIST------\n");
//	print_tokens(parser->tokens_list);
	parse_tokens(parser, mini_data);
//	printf("-------CMD LIST------\n");
//	print_cmd_list(mini_data->commands);
	free(mini_data->command_line);
	mini_data->command_line = NULL;
}

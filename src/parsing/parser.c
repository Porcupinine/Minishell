//
// Created by Laura Praca Lacerda on 8/7/23.
//
#include "../../include/minishell.h"
#include "../../Lib42/include/libft.h"
#include "../../include/lexical_analyzer.h"
#include "../../include/token_list_actions.h"
#include "../../include/cmd_list_actions.h"
#include <stdio.h>

void parse(t_data *mini_data)
{
	t_state_machine	*parser;

	parser = ft_calloc(1, sizeof (t_state_machine));
	if (parser == NULL)
		ft_error("Malloc fail\n");
	parse_machine(mini_data, parser);
	printf("------TOKEN LIST------\n");
	print_tokens(parser->tokens_list);
	parse_tokens(parser, mini_data);
	printf("-------CMD LIST------\n");
	print_cmd_list(mini_data->commands);
}
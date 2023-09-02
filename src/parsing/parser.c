/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 08:01:47 by laura             #+#    #+#             */
/*   Updated: 2023/09/01 15:32:51 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Lib42/include/libft.h"
#include "../../include/lexical_analyzer.h"
#include <stdio.h>

int	parse(t_data *mini_data)
{
	t_state_machine	*parser;

	parser = ft_calloc_exit(1, sizeof (t_state_machine));
	if (parse_machine(mini_data, parser) == 1)
	{

		return (1);
	}
	mini_data->exit_code = parser->exit_code;
	parser->exit_code = 0;
	if (mini_data->exit_code == 0)
	{
		parse_tokens(parser, mini_data);
		mini_data->exit_code = parser->exit_code;
	}
	free(mini_data->command_line);
	mini_data->command_line = NULL;
	free(parser);
	parser = NULL;
	return (0);
}

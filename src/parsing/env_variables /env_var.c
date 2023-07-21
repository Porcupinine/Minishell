/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_var.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 17:26:37 by laura         #+#    #+#                 */
/*   Updated: 2023/07/17 17:26:55 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include <stdlib.h>
#include "libft.h"
#include "../../../include/lexical_analyzer.h"
#include "../../../include/arg_list_actions.h"

void search_arg(t_data *mini_data, t_tokens *tokens)
{
	int count;
	char *name;
	char *content;
	int start;

	start = 0;
	count = 0;
	if(ft_strchr(tokens->str, '=') != 0)
	{
		while (tokens->str[count] != '=')
			count++;
		name = ft_substr(tokens->str, 0, count);
		start = count++;
		while (tokens->str[count] != '\0')
			count++;
		content = ft_substr(tokens->str, start, count-start);
		add_arg(mini_data->env_args, name, content);
	}
}

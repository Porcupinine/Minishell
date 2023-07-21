#include "../../../include/minishell.h"
#include <stdlib.h>
#include "libft.h"
#include "../../../include/lexical_analyzer.h"
#include "../../../include/env_var.h"

int search_envp(t_data *mini_data, char *str)
{
	int i;

	i = 0;
	while (mini_data->mini_envp[i])
	{
		if (ft_strncmp(mini_data->mini_envp[i], str, ft_strlen(str)) == 0)
			return(0);
		i++;
	}
	return (1);
}

void parse(t_state_machine *parser, t_data *mini_data)
{
	if (fin)
	while (parser->tokens_list)
	{
		if (parser->tokens_list->type == T_CHAR)
		{
			if (search_envp(mini_data, parser->tokens_list->str) == 0)
				//add new cmd with following char types;
				;
			else
				// add to arg list
				;
		}
	}
}
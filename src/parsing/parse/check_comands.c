#include "../../../include/minishell.h"
#include <stdlib.h>
#include "libft.h"
#include "../../../include/lexical_analyzer.h"
#include "../../../include/env_var.h"
#include "../../../include/token_list_actions.h"

void parse(t_state_machine *parser, t_data *mini_data)
{
	if (parser->tokens_list->type != T_PIPE)
		//TODO houston we have a problem
	while (parser->tokens_list)
	{
		if (parser->tokens_list->type == T_CHAR)
		{
			//add node
			while (parser->tokens_list->type != T_PIPE)
			{
				if (parser->tokens_list->type == T_BIG || parser->tokens_list->type == T_BIGBIG
					|| parser->tokens_list->type == T_SMALL || parser->tokens_list->type == T_SMALLSMALL)
					;
//				else
//					ft_strlcat(temp, parser->tokens_list->str, ft_strlen(parser->tokens_list->str));
//				parser->tokens_list = parser->tokens_list->next;
			}
		}
		if (parser->tokens_list->type == T_BIG || parser->tokens_list->type == T_BIGBIG
			|| parser->tokens_list->type == T_SMALL || parser->tokens_list->type == T_SMALLSMALL)
			;
	}
}
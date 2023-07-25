#include "../../../include/minishell.h"
#include <stdlib.h>
#include "libft.h"
#include "../../../include/lexical_analyzer.h"
#include "../../../include/env_var.h"
#include "../../../include/token_list_actions.h"

void parse(t_state_machine *parser, t_data *mini_data)
{
	t_commands *cmd;
	t_tokens *it_token;

	it_token = parser->tokens_list;
	cmd = NULL;
	if (parser->tokens_list->type != T_PIPE)
		//TODO houston we have a problem
	while (parser->tokens_list)
	{
		cmd = ft_calloc(1*sizeof (t_commands));
		if (cmd == NULL)
			//TODO erro;
		if (parser->tokens_list->type == T_CHAR
		{
			//add node
			while (parser->tokens_list->type != T_PIPE)
			{
//				if (parser->tokens_list->type == T_BIG || parser->tokens_list->type == T_BIGBIG
//					|| parser->tokens_list->type == T_SMALL || parser->tokens_list->type == T_SMALLSMALL)
//					;
////				else
////					ft_strlcat(temp, parser->tokens_list->str, ft_strlen(parser->tokens_list->str));
////				parser->tokens_list = parser->tokens_list->next;
			}
			add_node(mini_data->cmds, cmd);
			cmd = NULL;
			it_token = it_token->next;
		}
		if (parser->tokens_list->type == T_BIG || parser->tokens_list->type == T_BIGBIG
			|| parser->tokens_list->type == T_SMALL || parser->tokens_list->type == T_SMALLSMALL)
			;
	}
}
#include "../../../include/minishell.h"
#include <stdlib.h>
#include "libft.h"
#include "../../../include/lexical_analyzer.h"
#include "../../../include/env_var.h"
#include "../../../include/token_list_actions.h"

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
	t_commands *cmd;

	cmd = ft_calloc(1, sizeof(t_commands));
	if(cmd == NULL)
		//TODO huston we have a problem return with error
	if (parser->tokens_list->type != T_PIPE)
		//TODO huston we have a problem
	while (parser->tokens_list)
	{
		if (parser->tokens_list->type == T_CHAR)
		{
			//add node
//			while (parser->tokens_list->type != T_PIPE)
//			{
//				if (parser->tokens_list->type == T_BIG || parser->tokens_list->type == T_BIGBIG
//					|| parser->tokens_list->type == T_SMALL || parser->tokens_list->type == T_SMALLSMALL)
//					;
//				else
//					ft_strlcat(temp, parser->tokens_list->str, ft_strlen(parser->tokens_list->str));
//				parser->tokens_list = parser->tokens_list->next;
//			}
		}
		if (parser->tokens_list->type == T_BIG || parser->tokens_list->type == T_BIGBIG
			|| parser->tokens_list->type == T_SMALL || parser->tokens_list->type == T_SMALLSMALL)
			;
	}
}
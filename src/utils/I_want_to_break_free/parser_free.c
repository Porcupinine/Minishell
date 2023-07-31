//
// Created by Laura Praca Lacerda on 7/31/23.
//

#include "../../include/minishell.h"
#include "../../include/lexical_analyzer.h"
#include <stdlib.h>

void free_token_list(t_tokens **tokens)
{
	t_tokens *tmp;

	tmp = NULL;
	if (tokens == NULL)
		return ;
	while(*tokens)
	{
		tmp = *tokens;
		*tokens = (*tokens)->next;
		free(tmp);
	}
}

void free_cmd_list (t_commands **cmd)
{
	t_commands *tmp;

	tmp = NULL;
	if (cmd == NULL)
		return ;
	while (*cmd)
	{
		tmp = *cmd;
		*cmd = (*cmd)->next;
		free(tmp);
	}
}
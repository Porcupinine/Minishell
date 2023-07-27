#include "../../../include/minishell.h"
#include <stdlib.h>
#include "libft.h"
#include "../../../include/lexical_analyzer.h"
#include "../../../include/env_var.h"
#include "../../../include/token_list_actions.h"
#include "../../../include/cmd_list_actions.h"

static void between_pipes(char *temp, enum s_type *type, t_commands **cmd, t_tokens **it_token)
{
	while ((*it_token) && (*it_token)->type == T_CHAR)
	{
		temp = ft_strjoin_space(temp, (*it_token)->str);
		(*it_token) = (*it_token)->next;
		(*cmd)->cmd = temp;
		//TODO espaćo
	}
	temp = "\0";
	if ((*it_token) && ((*it_token)->type == T_BIG || (*it_token)->type == T_BIGBIG
						|| (*it_token)->type == T_SMALL || (*it_token)->type == T_SMALLSMALL))
	{
		(*type) = (*it_token)->type;
		(*it_token) = (*it_token)->next; // need to check if exists ?
	}
	if ((*it_token) && (*it_token)->type != T_CHAR)
		//TODO Houston we have a problem
		;
	else if ((*it_token))
	{
		add_inout(cmd, (*it_token)->str, (*type));
		(*it_token) = (*it_token)->next;
	}
}

static void token_iter(const t_data *mini_data, t_commands **cmd, t_tokens **it_token, char *temp, enum s_type *type)
{
	while ((*it_token))
	{
		(*cmd) = ft_calloc(1,sizeof (t_commands));
		if ((*cmd) == NULL)
			;//TODO erro
		while ((*it_token) && (*it_token)->type != T_PIPE)
		{
			between_pipes(temp, type, cmd, it_token);
		}
		if ((*cmd) != NULL)
		{
			add_cmd_node(&mini_data->cmds, (*cmd));
			(*cmd) = NULL;
			if((*it_token))
				(*it_token) = (*it_token)->next;
		}
	}
}

void parse(t_state_machine *parser, t_data *mini_data)
{
	t_commands *cmd;
	t_tokens *it_token;
	char *temp;
	enum s_type type;

	it_token = parser->tokens_list;
	cmd = NULL;
	temp = ft_calloc(1,sizeof (char *));
	if(temp == NULL)
		;//TODO malloc fail
	if (it_token->type != T_PIPE)
		//TODO houston we have a problem
		token_iter(mini_data, &cmd, &it_token, temp, &type);
}
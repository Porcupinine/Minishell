#include "../../../include/minishell.h"
#include <stdlib.h>
#include "libft.h"
#include "../../../include/lexical_analyzer.h"
#include "../../../include/env_var.h"
#include "../../../include/token_list_actions.h"
#include "../../../include/cmd_list_actions.h"
#include "../../../include/I_want_to_break_free.h"
#include "../../../include/errors.h"

extern int g_exit_code;

void extract_cmd(t_tokens **it_token, t_commands **cmd)
{
	char		*temp;
	char 		*temp2;

	temp = ft_calloc(1, sizeof(char));
	if (temp == NULL)
		ft_error("Malloc fail\n");
	while ((*it_token) && (*it_token)->type == T_CHAR)
	{
		temp2 = temp;
		temp = ft_strjoin_space(temp, (*it_token)->str);
		free(temp2);
		(*it_token) = (*it_token)->next;
	}
	(*cmd)->cmd = temp;
}

void between_pipes(t_tokens **it_token, t_commands **cmd, t_data *mini_data,
				   t_state_machine *parser)
{
	enum s_type	type;

	while ((*it_token) && (*it_token)->type != T_PIPE)
	{
		extract_cmd(it_token, cmd);
		if ((*it_token) && ((*it_token)->type == T_BIG || \
				(*it_token)->type == T_BIGBIG || (*it_token)->type == T_SMALL || \
				(*it_token)->type == T_SMALLSMALL))
		{
			(type) = (*it_token)->type;
			(*it_token) = (*it_token)->next;
			if ((*it_token) && (*it_token)->type == T_CHAR)
			{
				add_inout(cmd, (*it_token)->str, (type));
				(*it_token) = (*it_token)->next;
			}
			else
				syntax_error_parse(parser, mini_data);
		}
	}
}

void	parse_tokens(t_state_machine *parser, t_data *mini_data)
{
	t_commands	*cmd;
	t_tokens	*it_token;

	it_token = parser->tokens_list;
	cmd = NULL;
	if (it_token == NULL)
		return;
	while ((it_token))
	{
		(cmd) = ft_calloc(1, sizeof(t_commands));
		if ((cmd) == NULL)
			ft_error("Malloc fail\n");
		between_pipes(&it_token, &cmd, mini_data, parser);
		if ((cmd) != NULL)
		{
			add_cmd_node(&mini_data->commands, (cmd));
			(cmd) = NULL;
			if ((it_token))
				(it_token) = (it_token)->next;
		}
	}
	free_token_list(&parser->tokens_list);
	parser->tokens_list = NULL;
}

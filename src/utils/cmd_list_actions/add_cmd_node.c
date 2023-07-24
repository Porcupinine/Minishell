#include "../../../include/minishell.h"
#include <stdlib.h>
#include "libft.h"
#include "../../../include/lexical_analyzer.h"
#include "../../../include/env_var.h"
#include "../../../include/token_list_actions.h"

void add_cmd_node(t_commands **cmd, t_tokens *token_head)
{
	char *temp;

	temp = "\0";
	while (token_head->type != T_PIPE)
			{
				if (token_head->type == T_BIG || token_head->type == T_BIGBIG
					|| token_head->type == T_SMALL || token_head->type == T_SMALLSMALL)
					;
				else
					ft_strlcat(temp, token_head->str, ft_strlen(token_head->str));
				token_head = token_head->next;
			}
}
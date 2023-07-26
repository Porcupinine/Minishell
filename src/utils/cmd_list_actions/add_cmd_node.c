#include "../../../include/minishell.h"
#include <stdlib.h>
#include "libft.h"
#include "../../../include/lexical_analyzer.h"
#include "../../../include/env_var.h"
#include "../../../include/token_list_actions.h"

static t_commands *find_last_cmd(t_commands *cmd)
{
	if (cmd == NULL)
		return (NULL);
	while (cmd->next != NULL)
		cmd = cmd->next;
	return(cmd);
}

void add_cmd_node(t_commands **cmd, t_commands *new_cmd)
{
	t_commands *last;

	last = NULL;
	if (*cmd == NULL)
		*cmd = new_cmd;
	else
	{
		last = find_last_cmd(*cmd);
		last->next = new_cmd;
	}
}
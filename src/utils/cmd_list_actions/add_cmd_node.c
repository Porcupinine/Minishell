/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 11:52:33 by laura             #+#    #+#             */
/*   Updated: 2023/09/01 17:18:28 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include <stdlib.h>
#include "../../../include/utils.h"

static t_commands	*find_last_cmd(t_commands *cmd)
{
	if (cmd == NULL)
		return (NULL);
	while (cmd->next != NULL)
		cmd = cmd->next;
	return (cmd);
}

void	add_cmd_node(t_commands **cmd, t_commands *new_cmd)
{
	t_commands	*last;

	last = NULL;
	if (*cmd == NULL)
		*cmd = new_cmd;
	else
	{
		last = find_last_cmd(*cmd);
		last->next = new_cmd;
	}
}

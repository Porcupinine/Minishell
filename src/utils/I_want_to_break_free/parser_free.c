/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_free.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/11 08:04:56 by laura         #+#    #+#                 */
/*   Updated: 2023/08/16 14:35:27 by lpraca-l      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/lexical_analyzer.h"
#include "../../include/I_want_to_break_free.h"
#include <stdlib.h>

void	free_token_list(t_tokens **tokens)
{
	t_tokens	*tmp;

	tmp = NULL;
	if (tokens == NULL)
		return ;
	while (*tokens)
	{
		tmp = *tokens;
		*tokens = (*tokens)->next;
		free(tmp);
	}
}

void	free_cmd_list(t_commands **cmd)
{
	t_commands	*tmp;

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

void	free_pid_list(t_pid **lst)
{
	t_pid	*tmp;

	tmp = NULL;
	if (lst == NULL)
		return ;
	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp);
	}
}

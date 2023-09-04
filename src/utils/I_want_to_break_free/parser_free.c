/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_free.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/11 08:04:56 by laura         #+#    #+#                 */
/*   Updated: 2023/09/04 14:13:07 by lpraca-l      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/lexical_analyzer.h"
#include <stdlib.h>

void	free_token_list(t_tokens **tokens)
{
	t_tokens	*tmp;

	tmp = NULL;
	if (*tokens == NULL)
		return ;
	tmp = *tokens;
	while (*tokens != NULL)
	{
		tmp = *tokens;
		free(tmp->str);
		*tokens = (*tokens)->next;
		free(tmp);
	}
}

void	free_infiles_list(t_infile *infiles)
{
	t_infile	*tmp;

	tmp = NULL;
	if (infiles == NULL)
		return ;
	while (infiles)
	{
		tmp = infiles;
		free(tmp->file);
		infiles = (infiles)->next;
		free(tmp);
	}
}

void	free_outfiles_list(t_outfile *outfiles)
{
	t_outfile	*tmp;

	tmp = NULL;
	if (outfiles == NULL)
		return ;
	while (outfiles)
	{
		tmp = outfiles;
		free(tmp->file);
		outfiles = (outfiles)->next;
		free(tmp);
	}
}

void	free_cmd_list(t_commands **cmd)
{
	t_commands	*tmp;

	tmp = NULL;
	if (cmd == NULL)
		return ;
	while (*cmd != NULL)
	{
		tmp = *cmd;
		*cmd = (*cmd)->next;
		if (tmp->infiles != NULL)
			free_infiles_list((tmp->infiles));
		if (tmp->outfiles != NULL )
			free_outfiles_list((tmp->outfiles));
		free(tmp->cmd);
		free(tmp);
		tmp = NULL;
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

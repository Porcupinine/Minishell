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
#include <stdlib.h>

void	free_token_list(t_tokens **tokens)
{
	t_tokens	*tmp;

	tmp = NULL;
	if (*tokens == NULL)
		return ;
	tmp = *tokens;
	while (tmp != NULL) {
		printf("%s\n", tmp->str);
		free(tmp->str);
		tmp = tmp->next;
	}

	while ((*tokens) != NULL)
	{
		if((*tokens)->str != NULL)
			free((*tokens)->str);
		tmp = *tokens;
		*tokens = (*tokens)->next;
		//free(tmp);
	}
}

void	free_infiles_list(t_infile **infiles)
{
	t_infile *tmp;

	tmp = NULL;
	if (infiles == NULL)
		return;
	while(*infiles)
	{
		tmp = *infiles;
		*infiles = (*infiles)->next;
		free(tmp);
	}
}

void	free_outfiles_list(t_outfile **outfiles)
{
	t_outfile *tmp;

	tmp = NULL;
	if (outfiles == NULL)
		return;
	while(*outfiles)
	{
		tmp = *outfiles;
		*outfiles = (*outfiles)->next;
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
//		free_infiles_list(&((*cmd)->infiles));
//		free_outfiles_list(&((*cmd)->outfiles));
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

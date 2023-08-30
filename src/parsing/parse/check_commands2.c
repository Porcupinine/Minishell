/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_commands2.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/11 07:55:33 by laura         #+#    #+#                 */
/*   Updated: 2023/08/16 14:40:47 by lpraca-l      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "libft.h"
#include "../../../include/lexical_analyzer.h"
#include "../../../include/env_var.h"
#include "../../../include/utils.h"

void	kill_heredoc_clean(t_state_machine *parser, t_data *mini_data, t_commands **cmd)
{
	free_token_list(&parser->tokens_list);
	parser->tokens_list = NULL;
	free_cmd_list(&mini_data->commands);
	mini_data->commands = NULL;
	free(cmd);
	parser->exit_code = 1;
}

void	extract_cmd(t_tokens **it_token, t_commands **cmd)
{
	char		*temp;
	char		*temp2;

	temp = ft_calloc_exit(1, sizeof(char));
	while ((*it_token) && (*it_token)->type == T_CHAR)
	{
		temp2 = temp;
		temp = ft_strjoin_space(temp, (*it_token)->str);
		free(temp2);
		(*it_token) = (*it_token)->next;
	}
	(*cmd)->cmd = temp;
}

static int	found_here(t_tokens **it_token, t_commands **cmd, t_data *mini_data,
						 t_state_machine *parser)
{
	pid_t 	pid;
	int stat;

	pid = fork();
	if (pid == -1)
		ft_error("Fork failed.\n"); // check
	if(pid == 0)
	{
		unset_signals();
		handle_heredoc(it_token, cmd, mini_data);
	}
	waitpid(pid, &stat, 0);
	if (WIFSIGNALED(stat))
	{
		kill_heredoc_clean(parser, mini_data, cmd);
		return (-1) ;
	}
	add_inout(cmd, "tmp_file", (*it_token)->type);
	(*it_token) = (*it_token)->next->next;
		return (0);
}

int	between_pipes(t_tokens **it_token, t_commands **cmd, t_data *mini_data, \
	t_state_machine *parser)
{
	enum s_type	type;

	while ((*it_token) && (*it_token)->type != T_PIPE)
	{
		extract_cmd(it_token, cmd);
		if ((*it_token) && ((*it_token)->type == T_BIG || \
		(*it_token)->type == T_BIGBIG || \
				(*it_token)->type == T_SMALL))
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
		if ((*it_token) && (*it_token)->type == T_SMALLSMALL)
			if(found_here(it_token, cmd, mini_data, parser) == -1)
				return (-1);
	}
	return (0);
}
//TODO remove quotes for echo


void	parse_tokens(t_state_machine *parser, t_data *mini_data)
{
	t_commands	*cmd;
	t_tokens	*it_token;

	it_token = parser->tokens_list;
	cmd = NULL;
	if (it_token == NULL)
		return ;
	while ((it_token))
	{
		(cmd) = ft_calloc_exit(1, sizeof(t_commands));
		if (between_pipes(&it_token, &cmd, mini_data, parser) == -1)
			return;
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

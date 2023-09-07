/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_commands.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmaessen <dmaessen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/11 07:55:33 by laura         #+#    #+#                 */
/*   Updated: 2023/09/06 00:21:11 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "libft.h"
#include "../../../include/lexical_analyzer.h"
#include "../../../include/utils.h"
#include "../../include/exec.h"

void	kill_heredoc_clean(t_state_machine *parser, \
		t_data *mini_data, t_commands **cmd)
{
	free_token_list(&parser->tokens_list);
	parser->tokens_list = NULL;
	free_cmd_list(&mini_data->commands);
	mini_data->commands = NULL;
	free_cmd_list(cmd);
	parser->exit_code = 1;
}

void	extract_cmd(t_tokens **it_token, t_commands **cmd, t_data *mini_data)
{
	char		*temp;
	char		*temp2;
	char		*exun;

	temp = ft_calloc_exit(1, sizeof(char));
	while ((*it_token) && (*it_token)->type == T_CHAR)
	{
		exun = expanded((*it_token)->str, mini_data);
		if (ft_strncmp(temp, "export", 6) != 0)
			remove_quotes2point0(&exun);
		temp2 = temp;
		temp = ft_strjoin_space(temp2, exun);
		free(temp2);
		free(exun);
		exun = NULL;
		temp2 = NULL;
		(*it_token) = (*it_token)->next;
	}
	(*cmd)->cmd = temp;
	temp = NULL;
}

static int	found_here(t_tokens **it_token, t_commands **cmd, \
	t_data *mini_data, t_state_machine *parser)
{
	pid_t	pid;
	int		stat;

	pid = fork();
	ignore_signals();
	if (pid == -1)
		ft_error("Fork failed.\n");
	if (pid == 0)
	{
		unset_signals();
		handle_heredoc(it_token, cmd, mini_data);
	}
	waitpid(pid, &stat, 0);
	if (WIFSIGNALED(stat))
	{
		kill_heredoc_clean(parser, mini_data, cmd);
		return (-1);
	}
	set_signals();
	add_inout(cmd, "tmp_file", (*it_token)->type, mini_data);
	(*it_token) = (*it_token)->next->next;
	return (0);
}

int	between_pipes(t_tokens **it_token, t_commands **cmd, t_data *mini_data, \
	t_state_machine *parser)
{
	enum s_type	type;

	while ((*it_token) && (*it_token)->type != T_PIPE)
	{
		if ((*it_token)->type == T_CHAR)
			extract_cmd(it_token, cmd, mini_data);
		if ((*it_token) && ((*it_token)->type == T_BIG || \
		(*it_token)->type == T_BIGBIG || \
				(*it_token)->type == T_SMALL))
		{
			(type) = (*it_token)->type;
			(*it_token) = (*it_token)->next;
			if ((*it_token) && (*it_token)->type == T_CHAR)
			{
				add_inout(cmd, (*it_token)->str, (type), mini_data);
				(*it_token) = (*it_token)->next;
			}
			else
				syntax_error_parse(parser, mini_data);
		}
		if ((*it_token) && (*it_token)->type == T_SMALLSMALL)
			if (found_here(it_token, cmd, mini_data, parser) == -1)
				return (-1);
	}
	return (0);
}

int	parse_tokens(t_state_machine *parser, t_data *mini_data)
{
	t_commands	*cmd;
	t_tokens	*it_token;

	it_token = parser->tokens_list;
	cmd = NULL;
	if (it_token == NULL)
		return (1);
	while ((it_token))
	{
		(cmd) = ft_calloc_exit(1, sizeof(t_commands));
		if (between_pipes(&it_token, &cmd, mini_data, parser) == -1)
			return (1);
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
	return (0);
}

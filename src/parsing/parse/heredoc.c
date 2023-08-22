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
#include <stdlib.h>
#include "libft.h"
#include "../../../include/lexical_analyzer.h"
#include "../../../include/env_var.h"
#include "../../../include/utils.h"
#include <readline/readline.h>
#include <readline/history.h>

void heredoc(t_tokens **it_token, t_commands **cmd, t_data *mini_data)
{
	char	*limiter;
	bool	quotes;
	char 	*line;

	quotes = false;
	(*it_token) = (*it_token)->next;
	limiter = ft_strdup((*it_token)->str);
	if(ft_strchr(limiter, '\'') != 0 || ft_strchr(limiter, '"') != 0)
		quotes = true;
	line = readline("> ");
	while (line != NULL)
	{
		if (ft_strlen(line) == ft_strlen(limiter) &&
			ft_strncmp(line, limiter, ft_strlen(limiter)) != 0)
			break;
		write ((*cmd)->in,line, ft_strlen(line));
		line = readline("> ");
	}

	//current token is heredoc
	 // next token is sfeword
	 //check for quotes need to be a pair, if they are, we ignore expantions, otherwise we go bunkers
	//free limiter
	// ignore heredoc if there is more than one
}

void handle_heredoc(t_tokens **it_token, t_commands **cmd, t_data *mini_data)
{
	(*cmd)->in = open("tmp_file", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	heredoc(it_token, cmd, mini_data);
	close((*cmd)->in);
}
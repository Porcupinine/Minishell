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
#include "../../include/exec.h"


char *no_quotes_lim(char *str)
{
	int		count;
	int		count_lim;
	char	*lim;

	count = 0;
	count_lim = 0;
	lim = ft_calloc_exit((ft_strlen(str) - 1), sizeof (char));
	while (str[count] != '\0')
	{
		if (str[count] != '\'' && str[count] != '"')
		{
			lim[count_lim] = str[count];
			count_lim++;
		}
		count++;
	}
	lim[count] = '\0';
	return(lim);
}

void	get_line(t_commands *const *cmd, t_data *mini_data, const char *limiter, bool quotes)
{
	char *line;

	line = readline("> ");
	while (line != NULL)
	{
		if (ft_strlen(line) == ft_strlen(limiter) &&
			ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			break;
		if (quotes == false)
		{
			while (ft_strchr(line, '$') != 0)
				line = expand_dollar(line, mini_data);
		}
		write ((*cmd)->in,line, ft_strlen(line));
		write ((*cmd)->in, "\n", 1);
		line = readline("> ");
	}
	free(line);
}

void heredoc(t_tokens **it_token, t_commands **cmd, t_data *mini_data)
{
	char	*limiter;
	char 	*line;
	bool	quotes;

	quotes = false;
	(*it_token) = (*it_token)->next;
	if(ft_strchr((*it_token)->str, '\'') != 0 || ft_strchr((*it_token)->str, '"') != 0)
	{
		limiter = no_quotes_lim((*it_token)->str);
		quotes = true;
	}
	else
		limiter = ft_strdup((*it_token)->str);
	get_line(cmd, mini_data, limiter, quotes);
	free(limiter);
	limiter = NULL;
}
//if quotes is false, aply expansion otherwise easy

void handle_heredoc(t_tokens **it_token, t_commands **cmd, t_data *mini_data)
{
	(*cmd)->in = open("tmp_file", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	heredoc(it_token, cmd, mini_data);
	close((*cmd)->in);
	exit(0);
}
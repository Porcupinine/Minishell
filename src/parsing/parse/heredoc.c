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

static int search_in_path(char **mini_envp)
{
	int count;

	count = 0;
	while (mini_envp[count])
	{

	}
{

}
}

void check_for_exp(char *str, t_data *mini_data)
{
	char *exp_line;

	exp_line = NULL;
	if (ft_strchr(str, '$') != 0)
	{
		search_in_path(mini_data->mini_envp);
	}
}

char *no_quotes_lim(char *str)
{
	int		count;
	int		count_lim;
	char	*lim;

	count = 0;
	count_lim = 0;
	lim = ft_calloc((ft_strlen(str) - 1), sizeof (char));
	if (lim == NULL)
		ft_error("Malloc fail!\n");
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
	line = readline("> ");
	while (line != NULL)
	{
		if (ft_strlen(line) == ft_strlen(limiter) &&
			ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			break;
		write ((*cmd)->in,line, ft_strlen(line));
		write ((*cmd)->in, "\n", 1);
		line = readline("> ");
	}
	free(limiter);
	limiter = NULL;
}
//if quotes is false, aply expansion otherwise easy

void handle_heredoc(t_tokens **it_token, t_commands **cmd, t_data *mini_data)
{
	(*cmd)->in = open("tmp_file", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	heredoc(it_token, cmd, mini_data);
	close((*cmd)->in);
}
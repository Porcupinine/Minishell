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

static char *search_in_path(char **mini_envp, char *arg) {
	int count;
	char *exp;
	int count_exp;
	int count_char;

	count_exp = 0;
	count_char = 0;
	exp = NULL;
	count = 0;
	while (mini_envp[count] != NULL)
	{
		if (ft_strncmp(mini_envp[count], arg, ft_strlen(arg)) == 0 && mini_envp[count][ft_strlen(arg)] == '=')
		{
			exp = ft_calloc(ft_strlen(mini_envp[count]) - ft_strlen(arg), sizeof(char));
			if (exp == NULL)
				ft_error("malloc fail\n");
			while (mini_envp[count][count_char] != '=')
				count_char++;
			count_char++;
			while(mini_envp[count][count_char] != '\0')
			{
				exp[count_exp] = mini_envp[count][count_char];
				count_char++;
				count_exp++;
			}
			return(exp);
		}
		count++;
	}
	return (NULL);
}

char *new_str(char *str, char *exp)
{
	char *new_str;
	int count_str;
	int count_exp;
	int count_new;

	count_new = 0;
	count_str = 0;
	count_exp = 0;
	new_str = ft_calloc((ft_strlen(str) + ft_strlen(exp)), sizeof (char)); //remover arg
	if (new_str == NULL)
		ft_error("malloc fail!\n");
	//new string must be old string puls current expansion
	while (str[count_str] != '\0')
	{
		if(str[count_str] == '$')
		{
			while (exp[count_exp] != '\0')
			{
				new_str[count_new] = exp[count_exp];
				count_exp++;
				count_new++;
			}
			while (str[count_str] != ' ' && str[count_str] != '\0')
				count_str++;
			while (str[count_str] != '\0')
			{
				new_str[count_new] = str[count_str];
				count_str++;
				count_new++;
			}
			return (new_str);
		}
		if (str[count_str] == '\0')
			return (new_str);
		new_str[count_new] = str[count_str];
		count_new++;
		count_str++;
	}
	return (new_str);
}

char *check_for_exp(char *str, t_data *mini_data)
{
	char *exp_line;
	int count;
	char *arg;
	int start;

	start = 0;
	count = 0;
	exp_line = NULL;
	arg = NULL;
	if (ft_strchr(str, '$') != 0)
	{
		while (str[count] != '\0')
		{
			if (str[count] == '$')
			{
				start = count;
				while (str[count] != ' ' && str[count] != '\0')
					count++;
				arg = ft_substr(str, start + 1, (count - start)-1);
				exp_line = search_in_path(mini_data->mini_envp, arg);
				str = new_str(str, exp_line);
				free(arg);
				free(exp_line);
				return(str);
			}
			count++;
		}
	}
	return (str);
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
				line = check_for_exp(line, mini_data);
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
	add_inout(cmd, "tmp_file", (*it_token)->type);
	heredoc(it_token, cmd, mini_data);
	close((*cmd)->in);
	(*it_token) = (*it_token)->next;
}
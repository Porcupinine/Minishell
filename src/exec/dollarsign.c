/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarsign.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domi <domi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:54:29 by dmaessen          #+#    #+#             */
/*   Updated: 2023/08/01 19:25:34 by domi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"

// char *expand_dollar(char *line, t_data *mini)
// {
// 	int i;
// 	int len;
// 	int dollar; // maybe put this count in an ft
// 	int d;
// 	char *arg; // to store he expantion
// 	char *new;

// 	i = 0;
// 	dollar = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == '$')
// 			dollar++;
// 		i++;
// 	}
// 	d = 0;
// 	while (d < dollar)
// 	{
// 		i = 0;
// 		len = 0;
// 		while (line[i])
// 		{
// 			if (line[i] == '$')
// 			{
// 				while (line[i] != ' ')
// 				{
// 					arg[len] = line[i];
// 					len++;
// 					i++;
// 				}
// 			new = find_arg(arg, mini); // search in path and local and store the expantion
// 			ft_strlcat(line[i - len], new, ft_strlen(new)); // is this len correct??
// 			free_stdin(new, arg);
// 			}
// 			i++;
// 		}
// 		d++;
// 	}
// 	return (line);
// }

// bool	dollar_check(t_data *mini) // laura takes care of this, syntax wise
// {
// 	bool 	quotes;
// 	int		s_quote;
// 	int		d_quote;
// 	int		i;
	
// 	i = 0;
// 	s_quote = 0;
// 	d_quote = 0;
// 	quotes = false;
// 	while (mini->commands->infiles->file[i])
// 	{
// 		if (mini->commands->infiles->file[i] == 34)
// 			s_quote += 1;
// 		if (mini->commands->infiles->file[i] == 39)
// 			d_quote += 1;
// 		i++;
// 	}
// 	if (s_quote % 2 == 0) // so they're in pair
// 		quotes = true;
// 	if (s_quote % 2 == 0)
// 		quotes = true;
// 	// if uneven do we want to then throw an error actually?? LAURA??
// 	return (quotes);
// }

// static char	*find_arg(char *arg, t_data *mini) // what am i doing, actually not doing with this function??
// {
// 	int	i;
// 	char *new;

// 	i = 0;
// 	arg = ft_strtrim(arg, '$');
// 	while (mini->mini_envp[i])
// 	{
// 		if (ft_strncmp(mini->mini_envp[i], arg, ft_strlen(arg)) == 0)
// 		{
// 			new = ft_strtrim(mini->mini_envp[i], arg); // do i need to protect this thing?? or free??
// 			break ;
// 		}
// 		i++;
// 	}
// 	if (new == NULL)
// 	{
// 		while (mini->env_args != NULL) // or is the ->next pointing to NULL ??
// 		{
// 			if (ft_strncmp(mini->env_args, arg, ft_strlen(arg)) == 0)
// 			{
// 				new = ft_strtrim(mini->env_args, arg); // do i need to protect this thing?? or free??
// 				break ;
// 			}
// 			mini->env_args = mini->env_args->next;
// 		}
// 	}
// 	if (new == NULL) // if ARG doesn't exist then replace with blank (not even a space)
// 		new[0] = '\0'; // meaning just nothing, right??
// 	return (new);
// }

int var_len(char *line, int start)
{
	int i;

	i = 0;
	if (line[start] == '?')
		return (start + 1);
	while (ft_isalnum(line[start + i]) || line[start + i] == '_')
	{
		if (line[start + i] == ' ')
			break ;
		i++;
	}
	return (start + i);
}

char *var_name(char *line, int start, int end)
{
	char *sub;
	char *name;

	sub = ft_substr(line, start, end);
	if (sub == NULL)
		ft_error("Malloc fail\n");
	name = ft_strjoin(sub, "=");
	if (name == NULL)
		ft_error("Malloc fail\n");
	free(sub);
	return (name);
}

char *search_envp(char *var, t_data *mini)
{
	int i;

	i = 0;
	// if (var[i] == '?')
		// do something here ??
	while (mini->mini_envp[i])
	{
		if (ft_strncmp(mini->mini_envp[i], var, ft_strlen(var)) == 0)
			return (ft_substr(mini->mini_envp[i], ft_strlen(var),
				ft_strlen(mini->mini_envp[i]) - ft_strlen(var)));
		i++;
	}
	return (ft_strdup(""));
}

char *var_replace(char **line, char *var_exp, int start, int end)
{
	char *sub;
	char *sub2;
	char *join;
	char *newline;

	sub = ft_substr(*line, 0, start - 1); // rm the dollar sign
	if (sub == NULL)
		ft_error("Malloc fail\n");
	join = ft_strjoin(sub, var_exp);
	if (join == NULL)
		ft_error("Malloc fail\n");
	sub2 = ft_substr(*line, end, ft_strlen(*line));
	if (sub2 == NULL)
		ft_error("Malloc fail\n");
	newline = ft_strjoin(join, sub2);
	if (newline == NULL)
		ft_error("Malloc fail\n");
	free(sub);
	free(join);
	free(sub2);
	// free(*line); // needed?
	return (newline);
}

int expand_var(char **line, t_data *mini, int start) // maybe no double pointer needed
{
	// strjoin or substr maybe
	// start now is already beyond the $ sign
	int 	end;
	int 	new_len_line;
	char 	*var;
	char	*var_exp;

	end = var_len(*line, start);
	if (end == start)
		return (start);
	var = var_name(*line, start, end - start);
	var_exp = search_envp(var, mini);
	new_len_line = (start - 1) + ft_strlen(var_exp);
	*line = var_replace(line, var_exp, start, end);
	free(var);
	return (new_len_line);
}
// edgecase: $? and $_ (automatic? shows last command but a newline if multiple commands ran)

char *expand_dollar(char *line, t_data *mini)
{
	int 	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			i = expand_var(&line, mini, i + 1); // i adds up here each time
		i++;
	}
	return (line);
}
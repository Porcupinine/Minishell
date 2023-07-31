/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarsign.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:54:29 by dmaessen          #+#    #+#             */
/*   Updated: 2023/07/31 14:46:27 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"

char *expand_dollar(char *line, t_data *mini)
{
	int i;
	int len;
	int dollar; // maybe put this count in an ft
	int d;
	char *arg; // to store he expantion
	char *new;

	i = 0;
	dollar = 0;
	while (line[i])
	{
		if (line[i] == '$')
			dollar++;
		i++;
	}
	d = 0;
	while (d < dollar)
	{
		i = 0;
		len = 0;
		while (line[i])
		{
			if (line[i] == '$')
			{
				while (line[i] != ' ')
				{
					arg[len] = line[i];
					len++;
					i++;
				}
			new = find_arg(arg, mini); // search in path and local and store the expantion
			ft_strlcat(line[i - len], new, ft_strlen(new)); // is this len correct??
			free_stdin(new, arg);
			}
			i++;
		}
		d++;
	}
	return (line);
}

bool	dollar_check(t_data *mini)
{
	bool 	quotes;
	int		s_quote;
	int		d_quote;
	int		i;
	
	i = 0;
	s_quote = 0;
	d_quote = 0;
	quotes = false;
	while (mini->commands->infiles->file[i])
	{
		if (mini->commands->infiles->file[i] == 34)
			s_quote += 1;
		if (mini->commands->infiles->file[i] == 39)
			d_quote += 1;
		i++;
	}
	if (s_quote % 2 == 0) // so they're in pair
		quotes = true;
	if (s_quote % 2 == 0)
		quotes = true;
	// if uneven do we want to then throw an error actually?? LAURA??
	return (quotes);
}
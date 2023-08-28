/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarsign.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:54:29 by dmaessen          #+#    #+#             */
/*   Updated: 2023/08/28 15:44:06 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"

extern int g_exit_code;

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
	if (var[i] == '?')
		return (ft_itoa(mini->exit_code)); // is this right?
	while (mini->mini_envp[i])
	{
		if (ft_strncmp(mini->mini_envp[i], var, ft_strlen(var)) == 0)
			return (ft_substr(mini->mini_envp[i], ft_strlen(var),
				ft_strlen(mini->mini_envp[i]) - ft_strlen(var)));
		i++;
	}
	return (ft_strdup("")); // protect this
}

char *var_replace(char **line, char *var_exp, int start, int end)
{
	char *sub;
	char *sub2;
	char *join;
	char *newline;

	sub = ft_substr(*line, 0, start - 1);
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
	//free(*line); // needed?
	return (newline);
}

int expand_var(char **line, t_data *mini, int start)
{
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

char *expand_dollar(char *line, t_data *mini)
{
	int 	i;

	// if (ft_strchr(line, '~') != NULL && ft_strlen(line) == 1)
	// 	line = ft_strdup("$HOME");
	while (ft_strchr(line, '$') != NULL)
	{
		i = 0;
		while (line[i])
		{
			if (line[i] == '$')
				i = expand_var(&line, mini, i + 1);
			i++;
		}
	}
	return (line);
}

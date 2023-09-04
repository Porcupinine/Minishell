/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollarsign.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmaessen <dmaessen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 13:54:29 by dmaessen      #+#    #+#                 */
/*   Updated: 2023/09/04 14:20:53 by lpraca-l      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"

char	*search_envp(char *var, t_data *mini)
{
	int	i;

	i = 0;
	if (var[i] == '?')
		return (ft_itoa(mini->exit_code));
	while (mini->mini_envp[i])
	{
		if (ft_strncmp(mini->mini_envp[i], var, ft_strlen(var)) == 0)
			return (ft_substr(mini->mini_envp[i], ft_strlen(var), \
				ft_strlen(mini->mini_envp[i]) - ft_strlen(var)));
		i++;
	}
	return (ft_strdup(""));
}

char	*var_replace(char **line, char *var_exp, int start, int end)
{
	char	*sub;
	char	*sub2;
	char	*join;
	char	*newline;

	sub = ft_substr(*line, 0, start - 1);
	join = ft_strjoin(sub, var_exp);
	sub2 = ft_substr(*line, end, ft_strlen(*line));
	newline = ft_strjoin(join, sub2);
	free(sub);
	free(join);
	free(sub2);
	return (newline);
}

int	expand_var(char **line, t_data *mini, int start)
{
	int		end;
	int		new_len_line;
	char	*var;
	char	*var_exp;

	end = var_len(*line, start);
	if (end == start)
		return (start);
	var = var_name(*line, start, end - start);
	var_exp = search_envp(var, mini);
	new_len_line = (start - 1) + (int)ft_strlen(var_exp);
	*line = var_replace(line, var_exp, start, end);
	free(var_exp);
	free(var);
	return (new_len_line);
}

char	*expand_dollar(char *line, t_data *mini)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	while (ft_strchr(line, '$') != NULL)
	{
		i = 0;
		tmp = line;
		while (line[i] != '\0')
		{
			if (line[i] == '$')
				i = expand_var(&line, mini, i + 1);
			if (line[i] == '\0')
				break ;
			i++;
		}
	}
	free (tmp);
	return (line);
}

char	*expanded(char *str, t_data *mini_data)
{
	char	*exp_str;

	exp_str = NULL;
	if ((ft_strchr(str, '\'') == 0 || (ft_strchr(str, '"') != 0 \
	&& ft_strchr_position(str, '\'') > ft_strchr_position(str, '"'))) \
	&& ft_strchr(str, '$') != 0)
	{
		exp_str = expand_dollar(str, mini_data);
		return (exp_str);
	}
	else
		return (str);
}

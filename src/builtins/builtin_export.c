/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmaessen <dmaessen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 13:25:10 by dmaessen      #+#    #+#                 */
/*   Updated: 2023/09/05 23:37:10 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"
#include "../../include/utils.h"

static int	go_export(t_data *mini, char *cmd)
{
	char	*name;
	char	**new;
	char	*tmp;
	char	*res;
	char	*tmp2;

	name = ft_substr(cmd, 0, len_equal(cmd));
	res = ft_substr(cmd, ft_strlen(name), ft_strlen(cmd));
	tmp2 = remove_quotes(res);
	if (replace_envp_var(mini, name, tmp2) == 0)
		return (set_exit_code(mini, 0), 0);
	tmp = ft_strjoin(name, tmp2);
	free(name);
	free(tmp2);
	new = add_line_envp(mini->mini_envp, tmp, mini);
	free(tmp);
	if (new == NULL)
		return (mini->exit_code);
	mini->mini_envp = new;
	return (set_exit_code(mini, 0), 0);
}

static int	validation_export(t_data *mini, char *str)
{
	if (ft_strchr(str, '=') == NULL && is_valid_noerror(str) == true)
		return (0);
	else if (check_cmd(str) == true)
		go_export(mini, str);
	else
		return (not_valid_id(str, mini), 1);
	return (0);
}

static void	check_bool(bool *s, bool *d, char c)
{
	if (c == 34 && *d == false && *s == false)
		*d = true;
	else if (c == 34 && *d == true)
		*d = false;
	if (c == 39 && *s == false && *d == false)
		*s = true;
	else if (c == 39 && *s == true)
		*s = false;
}

static int	export_withquotes(t_data *mini, char *str, int i, int j)
{
	bool	s;
	bool	d;
	char	*tmp;

	s = false;
	d = false;
	while (str[i])
	{
		check_bool(&s, &d, str[i]);
		if ((str[i] == ' ' && d == false && s == false)
			|| (str[i + 1] == '\0' && (d == false && s == false)))
		{
			if (str[i + 1] == '\0')
				i++;
			tmp = ft_substr(str, j, (i - j));
			validation_export(mini, tmp);
			free(tmp);
			j = i;
			j++;
		}
		if (str[i] != '\0')
			i++;
	}
	return (0);
}

int	builtin_export(t_data *mini, char **cmd, char *str)
{
	int	i;

	if (!cmd[1] && ft_strlen(cmd[0]) == 6)
		print_xenv(mini);
	if (!cmd[1] && ft_strlen(cmd[0]) > 6)
		no_command(cmd, mini);
	if (ft_strchr(str, 39) == 0 && ft_strchr(str, 34) == 0)
	{
		i = 0;
		while (cmd[++i])
		{
			if (ft_strchr(cmd[i], '=') == NULL
				&& is_valid_noerror(cmd[i]) == true)
				continue ;
			else if (check_cmd(cmd[i]) == true)
				go_export(mini, cmd[i]);
			else
				not_valid_id(cmd[i], mini);
		}
	}
	else
		export_withquotes(mini, str, 7, 7);
	return (mini->exit_code);
}

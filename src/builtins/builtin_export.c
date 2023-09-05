/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:25:10 by dmaessen          #+#    #+#             */
/*   Updated: 2023/09/05 12:40:34 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"
#include "../../include/utils.h"

static void	print_xenv(t_data *mini)
{
	int	i;
	int	j;

	i = 0;
	while (mini->mini_envp[i])
	{
		ft_putstr_fd("declare -x ", 1);
		j = 0;
		while (mini->mini_envp[i][j])
		{
			if (mini->mini_envp[i][j] == '=')
				ft_putstr_fd("=\"", 1);
			else
				ft_putchar_fd(mini->mini_envp[i][j], 1);
			j++;
		}
		ft_putstr_fd("\"\n", 2);
		i++;
	}
	set_exit_code(mini, 0);
}

static char	**add_line_envp(char **envp, char *cmd, int size, t_data *mini)
{
	char	**new;
	int		i;

	new = ft_calloc_exit((size + 1), sizeof(char *));
	i = 0;
	while (envp[i] && i < size - 1)
	{
		new[i] = ft_strdup(envp[i]);
		i++;
	}
	cmd = expand_dollar(cmd, mini); // this is needed, not rm??
	if (cmd[0] == '=')
		return (not_valid_identifier_s(&cmd, mini), free(new), NULL);
	new[i] = ft_strdup(cmd);
	new[size] = NULL;
	free_str(envp);
	return (new);
}

static int	go_export(t_data *mini, char *cmd)
{
	char	*name;
	int		i;
	char	**new;
	int		size;
	char 	*tmp;
	char	*res; // new


	name = ft_substr(cmd, 0, len_equal(cmd));
	res = ft_substr(cmd, ft_strlen(name), ft_strlen(cmd)); // new
	res = remove_quotes(res); // new
	i = 0;
	while (mini->mini_envp[i])
	{
		if (ft_strncmp(mini->mini_envp[i], name,
				ft_strlen(name) - 1) == 0)
		{
			tmp = ft_strdup("");
			free(mini->mini_envp[i]);
			printf("cmd = %s -- name = %s -- res = %s -- tmp = %s\n", cmd, name, res, tmp);
			// mini->mini_envp[i] = ft_strjoin(tmp, cmd);
			mini->mini_envp[i] = ft_strjoin(name, res); // new
			return (free(name), set_exit_code(mini, 0), 0);
			// return (free(tmp), free(name), set_exit_code(mini, 0), 0);
		}
		i++;
	}
	tmp = ft_strjoin(name, res); // new
	printf("cmd = %s -- name = %s -- res = %s -- tmp = %s\n", cmd, name, res, tmp);
	free(name);
	//free(res); // new
	size = size_envp(mini);
	new = add_line_envp(mini->mini_envp, tmp, size + 1, mini); // tmp instead of cmd here
	free(tmp);
	if (new == NULL)
		return (mini->exit_code);
	mini->mini_envp = new;
	return (set_exit_code(mini, 0), 0);
}

static int validation_export(t_data *mini, char *str)
{
	if (ft_strchr(str, '=') == NULL && is_valid_noerror(str) == true)
		return (0);
	else if (check_cmd(str) == true)
		go_export(mini, str);
	else
		return (not_valid_identifier(&str, mini), 1);
	return (0);
}

static int export_withquotes(t_data *mini, char *str, int i, int j)
{
	bool s;
	bool d;
	char *tmp;

	s = false;
	d = false;
	while (str[i])
	{
		if (str[i] == 34 && d == false && s == false)
			d = true;
		else if (str[i] == 34 && d == true)
			d = false;
		if (str[i] == 39 && s == false && d == false)
			s = true;
		else if (str[i] == 39 && s == true)
			s = false;
		if ((str[i] == ' ' && d == false && s == false)
			|| (str[i + 1] == '\0' && (d == false || s == false)))
		{
			printf("BEF SUBSTR -- j = %d -- i = %d\n", j, i);
			tmp = ft_substr(str, j, i); // goes wrong here still takes the rest of the str not till i
			printf("tmp = %s -- j = %d -- i = %d\n", tmp, j, i);
			if (validation_export(mini, tmp) == 1)
				return (1);
			free(tmp);
			tmp = NULL;
			//i++;
			j = i;
			j++;
		}
		i++;
	}
	return (0);
}

int	builtin_export(t_data *mini, char **cmd, char *str) // add rm quotes to this function
{
	int	i;

	if (!cmd[1] && ft_strlen(cmd[0]) == 6)
		print_xenv(mini);
	if (!cmd[1] && ft_strlen(cmd[0]) > 6)
		no_command(cmd, mini);
	if (ft_strchr(str, 39) == 0 && ft_strchr(str, 34) == 0)
	{
		i = 1;
		while (cmd[i])
		{
			if (ft_strchr(cmd[i], '=') == NULL && is_valid_noerror(cmd[i]) == true)
				i++;
			else if (check_cmd(cmd[i]) == true)
			{
				go_export(mini, cmd[i]);
				i++;
			}
			else
				return (not_valid_identifier(cmd, mini), 1);
		}
	}
	else
		export_withquotes(mini, str, 7, 7); // check on succes??
	return (mini->exit_code);
}

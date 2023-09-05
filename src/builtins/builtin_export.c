/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmaessen <dmaessen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/27 13:25:10 by dmaessen      #+#    #+#                 */
/*   Updated: 2023/09/05 19:58:49 by laura         ########   odam.nl         */
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
	// cmd = expand_dollar(cmd, mini); // this is needed, not rm??
	if (cmd[0] == '=')
		return (not_valid_identifier_s(&cmd, mini), free(new), NULL);
	new[i] = ft_strdup(cmd);
	new[size] = NULL;
	free_str(envp);
	return (new);
}

static int replace_envp_var(t_data *mini, char *name, char *res)
{
	int i;

	i = 0;
	while (mini->mini_envp[i])
	{
		if (ft_strncmp(mini->mini_envp[i], name,
				ft_strlen(name) - 1) == 0)
		{
			free(mini->mini_envp[i]);
			free(res);
			mini->mini_envp[i] = ft_strjoin(name, res);
			return (free(name), set_exit_code(mini, 0), 0);
		}
		i++;
	}
	return (1);
}

static int	go_export(t_data *mini, char *cmd)
{
	char	*name;
	char	**new;
	int		size;
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
	size = size_envp(mini);
	new = add_line_envp(mini->mini_envp, tmp, size + 1, mini);
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

static void check_bool(bool *s, bool *d, char c)
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
			tmp = ft_substr(str, j , (i - j));
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

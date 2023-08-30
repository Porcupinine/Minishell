/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:09:12 by dmaessen          #+#    #+#             */
/*   Updated: 2023/08/30 11:32:07 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"
#include "../../include/utils.h"

int	builtin_cd(t_data *mini, char **cmd)
{
	char	*path;
	int		res;
	
	if (*mini->mini_envp == NULL)
		return (error_msg("envp not found\n", mini), -1); // TODO laura is this okay?
	if ((ft_strncmp(cmd[0], "cd\0", 2) == 0 && !cmd[1])
 		|| (ft_strncmp(cmd[1], "~", 1) == 0 && !cmd[2]))
	{
		path = search_path(mini, "HOME=");
		if (path != NULL)
			if (change_oldpwd(mini) != 0)
				return (mini->exit_code);
		res = chdir(path);
		free(path);
		if (res != 0)
			return (not_set("cd", "HOME not set", mini), 1);
		change_pwd(mini);
		return (set_exit_code(mini, 0), 0);
	}
	else
		search_specific_path(mini, cmd[1]); // is the below needed then??
	return (mini->exit_code);
}

char	*search_path(t_data *mini, char *target)
{
	int	i;

	i = 0;
	while (mini->mini_envp[i])
	{
		if (ft_strncmp(mini->mini_envp[i], target, ft_strlen(target)) == 0)
			return (ft_substr(mini->mini_envp[i], ft_strlen(target),
				ft_strlen(mini->mini_envp[i]) - ft_strlen(target)));
		i++;
	}
	return (NULL);
}

int	search_specific_path(t_data *mini, char *cmd)
{
	char		*tmp;
	struct stat	info;

	tmp = cmd;
	if (stat(tmp, &info) == 0)
	{
		if (change_oldpwd(mini) == 1)
			return (not_set("cd", "OLDPWD not set", mini), 1);
		if (S_ISDIR(info.st_mode))
		{
			if (tmp[ft_strlen(tmp)] != '/')
				tmp = ft_strjoin(tmp, "/");
		}
		if (chdir(tmp) != 0)
			return (not_directory_cd(cmd, mini), 1);
		free(tmp);
		change_pwd(mini); 
	}
	else
		return (not_directory_cd(cmd, mini), 1);
	return (set_exit_code(mini, 0), 0);
}

int	change_oldpwd(t_data *mini)
{
	char *pwd;
	char *tmp;
	int i;
	int len;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (set_exit_code(mini, errno),
			err_msg("getcwd", "failed"), -1);
	i = 0;
	while (mini->mini_envp[i])
	{
		if (ft_strncmp(mini->mini_envp[i], "OLDPWD=", 7) == 0)
		{
			tmp = mini->mini_envp[i];
			mini->mini_envp[i] = ft_strjoin("OLDPWD=", pwd);
			free(tmp);
			if (mini->mini_envp[i] == NULL)
				return (-1); // TODO check
			break ;
		}
		i++;
	}
	len = array_size(mini->mini_envp);
	if (len == i)
		return (not_set("cd", "OLDPWD not set", mini), 1);
	free(pwd);
	return (set_exit_code(mini, 0), 0);
}

int	change_pwd(t_data *mini)
{
	char *pwd;
	int i;
	char *tmp;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (-1); // TODO check if needs to be NULL
	i = 0;
	while (mini->mini_envp[i])
	{
		if (ft_strncmp(mini->mini_envp[i], "PWD=", 4) == 0)
		{
			tmp = mini->mini_envp[i];
			mini->mini_envp[i] = ft_strjoin("PWD=", pwd);
			free(tmp);
			if (mini->mini_envp[i] == NULL)
				return (-1); // TODO check if needs to be NULL
			break ;
		}
		i++;
	}
	free(pwd);
	return (0);
}

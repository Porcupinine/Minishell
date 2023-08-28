/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:09:12 by dmaessen          #+#    #+#             */
/*   Updated: 2023/08/28 15:02:09 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"
#include "../../include/utils.h"

/*
	abs path describe the location from the root directory
	relative path takes you below your current one

	if only cd --> takes you back to home directory
	if cd . --> don't implement
	if cd .. --> don't implement
	if cd ../../.. --> check if backslash present else add it yoruself
	if cd xx/ --> check if backslash present else add it yoruself
*/

int	builtin_cd(t_data *mini, char **cmd)
{
	char *path;
	int		res;
	
	if (*mini->mini_envp == NULL)
		return (-1); // TODO check if needs to be NULL
	if ((ft_strncmp(cmd[0], "cd\0", 2) == 0 && !cmd[1])
 		|| (ft_strncmp(cmd[1], "~", 1) == 0 && !cmd[2]))
	{
		path = search_path(mini, "HOME=");
		if (path != NULL)
			if (change_oldpwd(mini) == 1)
				return (not_set("cd", "OLDPWD not set"), 1);
		res = chdir(path);
		free(path);
		if (res != 0)
			return (not_set("cd", "HOME not set"), 1);
		change_pwd(mini);
		return (0);
	}
	else // a specified path
	{
		search_specific_path(mini, cmd[1]); // is the below needed then??
		return (0); // check
	}
	return (-1); // is this correct
}

char *search_path(t_data *mini, char *target)
{
	int i;

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

int search_specific_path(t_data *mini, char *cmd)
{
	char *tmp;
	struct stat info;

	tmp = cmd;
	if (stat(tmp, &info) == 0) // do something if != 0 ??
	{
		if (change_oldpwd(mini) == 1)
			return (not_set("cd", "OLDPWD not set"), 1);
		if (S_ISDIR(info.st_mode)) // check if the path leads is a directory
		{
			if (tmp[ft_strlen(tmp)] != '/')
				tmp = ft_strjoin(tmp, "/");
		}
		if (chdir(tmp) != 0)
			return (not_directory_cd(cmd), 1);
		free(tmp);
	}
//		return (builtin_err2("cd", str, "Not a directory\n"), 1); // check
	change_pwd(mini); 
	return (0); // check
}

int change_oldpwd(t_data *mini)
{
	char *pwd;
	char *tmp;
	int i;
	int len;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (-1); // TODO check if needs to be NULL
	i = 0;
	while (mini->mini_envp[i])
	{
		if (ft_strncmp(mini->mini_envp[i], "OLDPWD=", 7) == 0)
		{
			tmp = mini->mini_envp[i];
			mini->mini_envp[i] = ft_strjoin("OLDPWD=", pwd);
			free(tmp);
			if (mini->mini_envp[i] == NULL)
				return (-1); // TODO check if needs to be NULL
			break ;
		}
		i++;
	}
	len = array_size(mini->mini_envp);
	if (len == i)
		return (1);
	free(pwd);
	return (0);
}

int change_pwd(t_data *mini) // can this one error??
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

// static int search_path_cd(t_data *mini)
// {
// 	int 		i;
// 	char 		*str;
// 	struct stat info;

// 	str = malloc((ft_strlen(mini->commands->cmd) - 2) * sizeof(char)); // -3 to skip cd and space but + 1 not null term
// 	if (str == NULL)
// 		ft_error("Malloc fail\n"); // TODO check if needs to be NULL
// 	i = 0;
// 	while (mini->commands->cmd[i + 3]) // here too +3 right??
// 	{
// 		str[i] = mini->commands->cmd[i + 3];
// 		i++;
// 	}
// 	// str[i] = '\0'; // needed??
// 	if (stat(str, &info) == 0) // do something if != 0 ??
// 	{
// 		change_oldpwd(mini); // check on a return value of what??
// 		if (S_ISDIR(info.st_mode)) // check if the path leads is a directory
// 		{
// 			if (str[ft_strlen(str)] != '/')
// 				str = ft_strjoin(str, "/");
// 		}
// 	}
// 	if (chdir(str) != 0)
// 	{
// 		not_directory(cmd);
// 		return (1);
// //		return (builtin_err2("cd", str, "Not a directory\n"), 1); // check
// 	}
// 	change_pwd(mini); // meaning if succeed so we need to undate this 
// 		// check on a return value or what??
// 	free(str);
// 	return (0); // check
	
// }

// int	builtin_cd(t_data *mini, char **cmd)
// {
// 	int i;
	
// 	if (*mini->mini_envp == NULL)
// 		return (-1); // TODO check if needs to be NULL
// 	if ((ft_strncmp(cmd[0], "cd\0", 2) == 0 && !cmd[1])
// 		|| (ft_strncmp(cmd[1], "~", 1) == 0 && !cmd[2]))
// 	{
// 		i = 0;
// 		while (mini->mini_envp[i])
// 		{
// 			if (ft_strncmp(mini->mini_envp[i], "HOME=", 5) == 0) // all good also if unset HOME as should error
// 			{
// 				change_oldpwd(mini); // meaning if succeed so we need to undate this 
// 				if (chdir(ft_substr(mini->mini_envp[i], 6, ft_strlen(mini->mini_envp[i]))) != 0)
// 				{
// 					permission_denied(cmd);
// 					return (1);
// 				}
// 				change_pwd(mini); // meaning if succeed so we need to undate this
// //					// check on a return value or what??
// 				return (0);
// 			}
// 			i++;
// 		}
// 	}
// 	else // a specified path
// 	{
// 		search_path_cd(mini); // is the below needed then??
// 		return (0);
// 	}
// 	return (-1); // is this correct
// }
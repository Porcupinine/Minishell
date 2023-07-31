/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:09:12 by dmaessen          #+#    #+#             */
/*   Updated: 2023/07/31 12:43:28 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/pipes.h"
#include "../../Lib42/include/libft.h"

#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/param.h>

/*
	abs path describe the location from the root directory
	relative path takes you below your current one

	if only cd --> takes you back to home directory
	if cd . --> don't implement
	if cd .. --> don't implement
	if cd ../../.. --> check if backslash present else add it yoruself
	if cd xx/ --> check if backslash present else add it yoruself
*/
int	builtin_cd(t_data *mini, char *cmd)
{
	int i;
	
	if (*mini->mini_envp == NULL)
		return (ft_exit(errno));
	if (ft_strchr(cmd, "cd\0") || ft_strchr(cmd, "cd ~\0")) // back to home directory
	{
		i = 0;
		while (mini->mini_envp[i])
		{
			if (ft_strncmp(mini->mini_envp[i], "HOME=", 5) == 0) // all good also if unset HOME as should error
			{
				change_oldpwd(mini); // meaning if succeed so we need to undate this 
				if (chdirft_substr(mini->mini_envp[i], 6, ft_strlen(mini->mini_envp[i])) != 0)
					return (builtin_err2("cd",
						ft_substr(mini->mini_envp[i], 6, ft_strlen(mini->mini_envp[i])),
						"Permission denied\n"), 1);
				change_pwd(mini); // meaning if succeed so we need to undate this 
					// check on a return value of what??
				return (0);
			}
			i++;
		}
	}
	else // a specified path
	{
		search_path_cd(mini); // is the below needed then??
		return (0);
	}
	return (-1); // is this correct
}

int search_path_cd(t_data *mini)
{
	int 		i;
	char 		*str;
	struct stat info;

	str = malloc((ft_strlen(mini->commands->cmd) - 2) * sizeof(char)); // -3 to skip cd and space but + 1 not null term
	if (str == NULL)
		return (NULL); // check here
	i = 0;
	while (mini->commands->cmd[i + 3]) // here too +3 right??
	{
		str[i] = mini->commands->cmd[i + 3];
		i++;
	}
	// str[i] = '\0'; // needed??
	if (stat(str, &info) == 0) // do something if != 0 ??
	{
		change_oldpwd(mini); // check on a return value of what??
		if (S_ISDIR(info.st_mode)) // check if the path leads is a directory
		{
			if (str[ft_strlen(str)] != "/")
				str = ft_strjoin(str, "/");
		}
	}
	if (chdir(str) != 0)
		return (builtin_err2("cd", str, "Not a directory\n"), 1); // check
	change_pwd(mini); // meaning if succeed so we need to undate this 
		// check on a return value of what??
	free(str);
	return (0); // check
	
}

int change_oldpwd(t_data *mini)
{
	char *pwd;
	int len;
	int i;
	int j;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (NULL); // check this exit tho
	len = ft_strlen(pwd);
	i = 0;
	j = 0;
	while (mini->mini_envp[i])
	{
		if (ft_strncmp(mini->mini_envp[i], "OLDPWD=", 7) == 0)
		{
			while ((j + 7) < len) // 7 or 8 here?? getting confused
			{
				mini->mini_envp[i][j + 8] = pwd[j]; // 7 or 8 here?? getting confused
				j++;
			}
			break ;
		}
		i++;
	}
	mini->mini_envp[i][j + 8] = '\0';
	free(pwd);
	return (0);
}

int change_pwd(t_data *mini)
{
	char *pwd;
	int len;
	int i;
	int j;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (NULL); // check this exit tho
	len = ft_strlen(pwd);
	i = 0;
	j = 0;
	while (mini->mini_envp[i])
	{
		if (ft_strncmp(mini->mini_envp[i], "PWD=", 4) == 0)
		{
			while ((j + 4) < len) // 4 or 5 here?? getting confused
			{
				mini->mini_envp[i][j + 5] = pwd[j]; // 4 or 5 here?? getting confused
				j++;
			}
			break ;
		}
		i++;
	}
	mini->mini_envp[i][j + 5] = '\0';
	free(pwd);
	return (0);
}

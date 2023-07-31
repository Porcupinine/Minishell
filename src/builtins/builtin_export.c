/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:25:10 by dmaessen          #+#    #+#             */
/*   Updated: 2023/07/31 14:46:50 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"

/*
	using export should add the mentionned variable to envp
	(not the same as our local arg list)

	// export a variable
	// do we support the = something ??
	// access envp
	// open with write rights and add a line for it
*/
int	builtin_export(t_data *mini, char *cmd)
{
	int end;
    int i;
	// char *str;
    char **str;
	int nb; // amount of args to export
    
	if (*mini->mini_envp == NULL)
		return (ft_exit(errno));
    cmd = ft_substr(cmd, 8, ft_strlen(cmd)); // needs protection?
	// if (cmd == NULL)
	// 	return (NULL); // needs protection?? if NULL??
	str = ft_split(cmd, " ");
	if (str == NULL)
		return (NULL);
	nb = 0;
	while (str[nb])
		nb++;
	end = 0;
	while (!mini->mini_envp[end])
		end++;
	mini->mini_envp[end + 1] = malloc((ft_strlen(cmd) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (cmd[i])
	{
		mini->mini_envp[end + 1][i] = cmd[i];
		i++;
	}
	mini->mini_envp[end + 1][i] = '\0'; // this ain't needed probably right ?? 
	// check if there is more than one arg to set here (could be ++)
	ft_free(str); // as its double pointer OR DOES THIS GET FREE UPON CLOSING OF THE PROG ONLY??
    return (0);
}

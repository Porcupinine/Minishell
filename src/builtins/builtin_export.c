/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:25:10 by dmaessen          #+#    #+#             */
/*   Updated: 2023/07/27 16:25:46 by dmaessen         ###   ########.fr       */
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
	int len;
    char **str;
    
	if (*mini->mini_envp == NULL)
		return (ft_exit(errno));
    cmd = ft_substr(cmd, 8, ft_strlen(cmd)); // needs protection??
    str = ft_split(cmd, "=");
	if (str == NULL)
		return (NULL); // needs protection?? if NULL??
	end = 0;
	while (!mini->mini_envp[end])
		end++;
	len = ft_strlen(str)
	
	// all depends if we use an array or a linekd list here
	// do i need to malloc the line ? PROBABLY YES

	// check if there is more than one arg to set here (could be ++)
    return (0);
}

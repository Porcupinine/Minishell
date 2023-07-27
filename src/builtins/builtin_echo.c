/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:09:31 by dmaessen          #+#    #+#             */
/*   Updated: 2023/07/27 13:15:19 by dmaessen         ###   ########.fr       */
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
	should it also handle echo $?  ??
	example to deal with the $ARG/$PATH expantion: printf("PATH : %s\n", getenv("PATH"));
	// one extra else if in case non-accepted flags, or does laura handle upfront?
	// for both handle the $ or not ?? think so
	// check if quotes
		// if yes check if they are closed
		// else needs to read from stdin
*/
int	builtin_echo(t_data *mini, char *cmd)
{
	if (ft_strncmp(mini->commands->cmd, "echo -n", 7) == 0) // probably if flag for echo or not instead of strncmp
	{
		// check if there is a $ still in there or not? LAURA
		printf("%s", mini->commands->cmd + 8);
	}
	else
	{
		// check if there is a $ still in there or not? LAURA
		printf("%s\n", mini->commands->cmd + 5);
	}
	return (0); // check
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:13:30 by dmaessen          #+#    #+#             */
/*   Updated: 2023/07/27 13:13:56 by dmaessen         ###   ########.fr       */
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

void	builtin_env(t_data *mini)
{
	int i;

	if (*mini->mini_envp == NULL)
		return (ft_exit(errno));
	i = 0;
	while (mini->mini_envp[i])
	{
		printf("%s\n", mini->mini_envp[i]);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:56:37 by dmaessen          #+#    #+#             */
/*   Updated: 2023/08/30 10:57:27 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"

void	free_fd(int **fd, int nb_cmds)
{
	int	nb;
	int	i;

	nb = nb_cmds;
	i = 0;
	while (i < nb)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}

void    set_exit_code(t_data *mini, int code)
{
	mini->exit_code = code;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:53:54 by dmaessen          #+#    #+#             */
/*   Updated: 2023/08/30 15:31:04 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"
#include "../../include/utils.h"

bool	check_cmd(char *cmd)
{
	int	i;

	if (cmd[0] == '=')
		return (false);
	i = 0;
	while (cmd[i] && cmd[i] != '=')
	{
		if (ft_isalnum(cmd[i]) == 0 && cmd[i] != '='
			&& cmd[i] != '_' && cmd[i] != '$' && cmd[i] != 92)
			return (false);
		i++;
	}
	return (true);
}

bool	is_valid_noerror(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (ft_isalnum(cmd[i]) == 0)
		{
			if (cmd[i] != '$' && cmd[i] != 92)
				return (false);
		}
		i++;
	}
	return (true);
}

int	len_equal(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '=')
		{
			i++;
			break ;
		}
		i++;
	}
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:32:30 by dmaessen          #+#    #+#             */
/*   Updated: 2023/09/06 16:12:34 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"
#include "../../include/utils.h"

#define LONG_MAXX 9223372036854775807

static void	throw_error(t_data *mini, char **cmd, long long nb, int i)
{
	if (i == 1)
	{
		numeric_arg_required(cmd, mini);
		mini->exit_code = nb % 256;
	}
	if (i == 2)
	{
		numeric_arg_required(cmd, mini);
		if (ft_strncmp(cmd[1], "-9223372036854775808", 20) == 0)
			mini->exit_code = 0;
	}
	if (i == 3)
	{
		numeric_arg_required(cmd, mini);
		mini->exit_code = 255;
	}
}

static long	ft_atoi_long(char *str, t_data *mini, char **cmd, long long nb)
{
	long		i;
	long		sign;

	nb = 0;
	i = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if ((str[i] >= 48 && str[i] <= 57))
			nb = (nb * 10) + (str[i] - 48);
		else
			return (throw_error(mini, cmd, nb, 3), -1);
		if (nb > LONG_MAXX)
			return (throw_error(mini, cmd, nb, 1), -1);
		i++;
	}
	if (nb < 0)
		return (throw_error(mini, cmd, nb, 2), -1);
	return ((long)(sign * nb));
}

void	builtin_exit(t_data *mini, char **cmd)
{
	long long	code;

	code = mini->exit_code;
	if (ft_strncmp(cmd[0], "exit", ft_strlen(cmd[0])) == 0 && cmd[1] == NULL)
	{
		if (mini->nb_cmds == 1)
			ft_putstr_fd("exit\n", 2);
		exit(code);
	}
	if (cmd[2] != NULL)
	{
		ft_putstr_fd("exit\n", 2);
		too_many_args(cmd, mini);
	}
	else
	{
		ft_putstr_fd("exit\n", 2);
		code = ft_atoi_long(cmd[1], mini, cmd, 0);
		if (code == -1)
			exit(mini->exit_code);
		code = code % 256;
		mini->exit_code = code;
		exit(code);
	}
}

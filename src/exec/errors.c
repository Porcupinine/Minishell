/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:20:42 by dmaessen          #+#    #+#             */
/*   Updated: 2023/09/04 13:41:12 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"

void	err_msg(char *cmd, char *str)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, str, ft_strlen(str));
}

void	error_msg(char *str, t_data *mini)
{
	write(2, "minishell: ", 11);
	write(2, str, ft_strlen(str));
	mini->mini_envp = 0;
}

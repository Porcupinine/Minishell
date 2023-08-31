/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:20:42 by dmaessen          #+#    #+#             */
/*   Updated: 2023/08/31 15:36:18 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"

int	    cmd_err(char *str, int error)
{
	perror(str);
	return (error); // but return as an exit
}

void	builtin_err(char *cmd, char *str) // USING
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, str, ft_strlen(str));
}

void	builtin_err2(char *cmd, char *arg, char *str)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, arg, ft_strlen(arg));
	write(2, ": ", 2);
	write(2, str, ft_strlen(str));
}

void	err_cmd_not_found(char **command)
{
	write(2, "minishell: ", 11);
	write(2, command[0], ft_strlen(command[0]));
	write(2, ": command not found\n", 21);
	free_str(command);
}

void	err_msg(char *cmd, char *str) // combine with builtin_err ?? // USING FOR PIPE ERROR
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
	mini->mini_envp = 0; // or -1??
}

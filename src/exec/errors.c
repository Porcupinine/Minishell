/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:20:42 by dmaessen          #+#    #+#             */
/*   Updated: 2023/08/02 08:55:16 by dmaessen         ###   ########.fr       */
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

void	builtin_err(char *cmd, char *str)
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

void	err_msg(char *cmd, char *str) // combine with builtin_err ??
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, str, ft_strlen(str));
}

// void	no_perm_err(int argc, char *argv[]) // from pipex -- RM/REWORK
// {
// 	if (access(argv[1], F_OK) == -1)
// 	{
// 		write(2, "pipex: ", 7);
// 		write(2, argv[1], ft_strlen(argv[1]));
// 		write(2, ": No such file or directory\n", 29);
// 	}
// 	else if (access(argv[1], R_OK) == -1)
// 	{
// 		write(2, "pipex: ", 7);
// 		write(2, argv[1], ft_strlen(argv[1]));
// 		write(2, ": permission denied\n", 21);
// 	}
// 	if (access(argv[argc - 1], W_OK | R_OK) == -1)
// 	{
// 		write(2, "pipex: ", 7);
// 		write(2, argv[argc - 1], ft_strlen(argv[argc - 1]));
// 		write(2, ": permission denied\n", 21);
// 		exit(errno);
// 	}
// }
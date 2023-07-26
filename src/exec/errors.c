/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:20:42 by dmaessen          #+#    #+#             */
/*   Updated: 2023/07/25 18:17:13 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <string.h>

int	    cmd_err(char *str, int error)
{
	perror(str);
	return (error); // but return as an exit
}

// void	no_perm_err(int argc, char *argv[]) // from pipex -- REWORK
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
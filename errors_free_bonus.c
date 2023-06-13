/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_free_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:46:37 by dmaessen          #+#    #+#             */
/*   Updated: 2023/06/13 15:13:00 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// review them all as they aren't true to "real" bash

void	cmd_err(char *argv, int error)
{
	perror(argv);
	exit(error);
}

void	free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	cmd_not_found(char **command)
{
	write(2, "pipex: ", 7);
	write(2, command[0], ft_strlen(command[0]));
	write(2, ": command not found\n", 21);
	free_str(command);
	exit(127);
}

void	no_perm_err(int argc, char *argv[])
{
	if (access(argv[1], F_OK) == -1)
	{
		write(2, "pipex: ", 7);
		write(2, argv[1], ft_strlen(argv[1]));
		write(2, ": No such file or directory\n", 29);
	}
	else if (access(argv[1], R_OK) == -1)
	{
		write(2, "pipex: ", 7);
		write(2, argv[1], ft_strlen(argv[1]));
		write(2, ": permission denied\n", 21);
	}
	if (access(argv[argc - 1], W_OK | R_OK) == -1)
	{
		write(2, "pipex: ", 7);
		write(2, argv[argc - 1], ft_strlen(argv[argc - 1]));
		write(2, ": permission denied\n", 21);
		exit(errno);
	}
}

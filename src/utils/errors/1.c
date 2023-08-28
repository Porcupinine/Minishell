/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domi <domi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 08:04:28 by laura             #+#    #+#             */
/*   Updated: 2023/08/28 11:18:57 by domi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/utils.h"
#include "../../include/exec.h"
#include <unistd.h>
#include "../../Lib42/include/libft.h"

// _: _: no such file or directory

extern int	g_exit_code;

void	no_file_directory(char **command)
{
	write(2, "minishell: ", 11);
	write(2, command[0], ft_strlen(command[0]));
	write(2, ": ", 2);
	write(2, command[1], ft_strlen(command[1]));
	write(2, ": ", 2);
	write(2, "No such file or directory\n", 26);
	g_exit_code = 1;
	free_str(command);
}

void	not_valid_identifier(char **command)
{
	write(2, "minishell: ", 11);
	write(2, command[0], ft_strlen(command[0]));
	write(2, ": `", 3);
	if (command[1][0] != 34 && command[1][1] != 34)
		write(2, command[1], ft_strlen(command[1]));
	write(2, "': ", 3);
	write(2, "not a valid identifier\n", 23);
	g_exit_code = 1;
	// free_str(command);
}

void	not_valid_identifier_s(char **command)
{
	write(2, "minishell: ", 11);
	write(2, "export: `", 9);
	write(2, command[0], ft_strlen(command[0]));
	write(2, "': ", 3);
	write(2, "not a valid identifier\n", 23);
	g_exit_code = 1;
	// free_str(command);
}

void	permission_denied(char **command)
{
	write(2, "minishell: ", 11);
	write(2, command[0], ft_strlen(command[0]));
	write(2, ": ", 2);
	write(2, command[1], ft_strlen(command[1]));
	write(2, ": ", 2);
	write(2, "permission denied\n", 18);
	g_exit_code = 1;
	free_str(command);
}

void	too_many_args(char **command)
{
	write(2, "minishell: ", 11);
	write(2, command[0], ft_strlen(command[0]));
	write(2, ": ", 2);
	write(2, "too many arguments\n", 19);
	g_exit_code = 1;
	free(command);
}

void	not_directory(char **command)
{
	write(2, "minishell: ", 11);
	write(2, command[0], ft_strlen(command[0]));
	write(2, ": ", 2);
	write(2, command[1], ft_strlen(command[1]));
	write(2, ": ", 2);
	write(2, "Not a directory\n", 17);
	g_exit_code = 1;
	free_str(command);
}

void	not_set(char *command, char *str)
{
	write(2, "minishell: ", 11);
	write(2, command, ft_strlen(command));
	write(2, ": ", 2);
	write(2, str, ft_strlen(str));
	g_exit_code = 1;
}

void	not_directory_cd(char *command)
{
	write(2, "minishell: ", 11);
	write(2, "cd: ", 4);
	write(2, command, ft_strlen(command));
	write(2, ": ", 2);
	write(2, "Not a directory\n", 17);
	g_exit_code = 1;
}
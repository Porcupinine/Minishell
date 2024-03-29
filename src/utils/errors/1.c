/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 08:04:28 by laura             #+#    #+#             */
/*   Updated: 2023/09/06 14:30:13 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/utils.h"
#include "../../include/exec.h"
#include <unistd.h>
#include "../../Lib42/include/libft.h"

void	no_file_directory(char **command, t_data *mini)
{
	write(2, "minishell: ", 11);
	write(2, command[0], ft_strlen(command[0]));
	write(2, ": ", 2);
	write(2, command[1], ft_strlen(command[1]));
	write(2, ": ", 2);
	write(2, "No such file or directory\n", 26);
	mini->exit_code = 1;
}

void	no_filedirectory(char *file, t_data *mini)
{
	write(2, "minishell: ", 11);
	write(2, file, ft_strlen(file));
	write(2, ": ", 2);
	write(2, "No such file or directory\n", 26);
	mini->exit_code = 1;
}

void	not_valid_identifier(char **command, t_data *mini)
{
	write(2, "minishell: ", 11);
	write(2, command[0], ft_strlen(command[0]));
	write(2, ": `", 3);
	if (command[1][0] != 34 && command[1][1] != 34)
		write(2, command[1], ft_strlen(command[1]));
	write(2, "': ", 3);
	write(2, "not a valid identifier\n", 23);
	mini->exit_code = 1;
}

void	not_valid_id(char *command, t_data *mini)
{
	write(2, "minishell: ", 11);
	write(2, "export", 6);
	write(2, ": `", 3);
	write(2, command, ft_strlen(command));
	write(2, "': ", 3);
	write(2, "not a valid identifier\n", 23);
	mini->exit_code = 1;
}

void	not_valid_identifier_s(char **command, t_data *mini)
{
	write(2, "minishell: ", 11);
	write(2, "export: `", 9);
	write(2, command[0], ft_strlen(command[0]));
	write(2, "': ", 3);
	write(2, "not a valid identifier\n", 23);
	mini->exit_code = 1;
}

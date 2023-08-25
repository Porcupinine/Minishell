/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   127.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 08:04:28 by laura             #+#    #+#             */
/*   Updated: 2023/08/25 15:19:35 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/utils.h"
#include <unistd.h>
#include "../../Lib42/include/libft.h"
#include "../../include/exec.h"

extern int	g_exit_code;

void	no_command(char **command, t_data *mini)
{
	write(2, "minishell: ", 11);
	if (ft_strncmp(command[0], "$?", 2) == 0)
		write(2, ft_itoa(mini->exit_code), ft_strlen(ft_itoa(mini->exit_code))); // doesn't seem to work properly
	else
		write(2, command[0], ft_strlen(command[0]));
	write(2, ": command not found\n", 21);
	g_exit_code = 127;
	//free_str(command); // else double free
}

void	no_filedir(char *str, char *command, t_data *mini)
{
	write(2, str, ft_strlen(str));
	write(2, ": ", 2);
	if (ft_strncmp(command, "$?", 2) == 0)
		write(2, ft_itoa(mini->exit_code), ft_strlen(ft_itoa(mini->exit_code))); // doesn't seem to work properly
	else
		write(2, command, ft_strlen(command));
	write(2, ": No such file or directory\n", 28);
	g_exit_code = 127;
}

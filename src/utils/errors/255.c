
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   1.c                                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/11 08:04:28 by laura         #+#    #+#                 */
/*   Updated: 2023/08/11 08:04:30 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/I_want_to_break_free.h"
#include <unistd.h>
#include "../../Lib42/include/libft.h"
#include "../../include/exec.h"

extern int g_exit_code;

void numeric_arg_required(char **command)
{
	write(2, "minishell: ", 11);
	write(2, command[0], ft_strlen(command[0]));
	write(2, ": ", 2);
	write(2, command[1], ft_strlen(command[1]));
	write(2, ": ", 2);
	write(2, "numeric argument require\n",25);
	g_exit_code = 255;
	free_str(command);
}
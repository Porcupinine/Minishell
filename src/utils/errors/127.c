/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   127.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 08:04:28 by laura             #+#    #+#             */
/*   Updated: 2023/08/21 16:06:20 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/I_want_to_break_free.h"
#include <unistd.h>
#include "../../Lib42/include/libft.h"
#include "../../include/exec.h"

extern int	g_exit_code;

void	no_command(char **command)
{
	write(2, "minishell: ", 11);
	write(2, command[0], ft_strlen(command[0]));
	write(2, ": command not found\n", 21);
	g_exit_code = 127;
	//free_str(command); // else double free
}

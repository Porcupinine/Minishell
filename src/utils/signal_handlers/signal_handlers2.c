/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handlers2.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lpraca-l <lpraca-l@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/04 14:10:43 by lpraca-l      #+#    #+#                 */
/*   Updated: 2023/09/04 14:11:07 by lpraca-l      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <termios.h>
#include <stdio.h>
#include "../../include/utils.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <unistd.h>

void	set_term(void)
{
	struct termios	term;

	tcgetattr(fileno(stdin), &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(fileno(stdin), 0, &term);
}

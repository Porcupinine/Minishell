/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handlers.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 14:06:41 by laura         #+#    #+#                 */
/*   Updated: 2023/08/31 14:06:42 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <termios.h>
#include <stdio.h>
#include "../../include/utils.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <unistd.h>


void	sigint_handler(int sig)
{
//	write(1, "\n", 1);
//	rl_redisplay();
	return_prompt();
//	(void)sig;
}

//TODO exit code

// if (!isatty(STDIN_FILENO))
//      rl_outstream = stdin;

void	sigquit_handler(int sig)
{
//	(void)sig;
}

void	set_term(void)
{
	struct termios	term;

	tcgetattr(fileno(stdin), &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(fileno(stdin), 0, &term);
}

void	unset_signals(void )
{
	signal(SIGINT, SIG_DFL);
//	write(1, "\n", 1);
	signal(SIGQUIT, SIG_DFL);
}

void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
//	struct sigaction	sigint_sa;
//	struct sigaction	sigquit_sa;
//
	set_term();
//	sigemptyset(&sigint_sa.sa_mask);
//	sigemptyset(&sigquit_sa.sa_mask);
//	sigquit_sa.sa_handler = &sigquit_handler;
//	sigint_sa.sa_handler = &sigint_handler;
//	sigaction(SIGQUIT, &sigquit_sa, NULL);
//	sigaction(SIGINT, &sigint_sa, NULL);
}

#include <signal.h>
#include <termios.h>
#include <stdio.h>
#include "../../include/utils.h"

void	sigint_handler(int sig)
{
	return_prompt();
	kill(0, SIGQUIT);
	//TODO TOP changes the signal, it can break minishell
}

// if (!isatty(STDIN_FILENO))
//      rl_outstream = stdin;

void	sigquit_handler(int sig)
{
//	rl_on_new_line();
//	rl_replace_line("", 0);
//	rl_redisplay();
}

void	set_term(void)
{
	struct termios term;

	tcgetattr(fileno(stdin), &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(fileno(stdin), 0, &term);
}

void	set_signals(void)
{
	struct sigaction	sigint_sa;
	struct sigaction	sigquit_sa;

	sigemptyset(&sigint_sa.sa_mask);
	sigemptyset(&sigquit_sa.sa_mask);
	sigquit_sa.sa_handler = &sigquit_handler;
	sigint_sa.sa_handler = &sigint_handler;
	sigaction(SIGQUIT, &sigquit_sa, NULL);
	sigaction(SIGINT, &sigint_sa, NULL);
}
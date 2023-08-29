#include <signal.h>
#include <termios.h>
#include <stdio.h>
#include "../../include/utils.h"
#include <stdlib.h>

void	sigint_handler(int sig)
{
	return_prompt();
	//TODO TOP changes the signal, it can break minishell WE DONT CARE!
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

//void	unset_sigint_handler(int sig)
//{
//	exit(0);
//}

void	unset_signals(void )
{
//	struct sigaction unset_sigint;
//
//	sigemptyset(&unset_sigint.sa_mask);
//	unset_sigint.sa_handler = &unset_sigint_handler;
//	sigaction(SIGINT, &unset_sigint, NULL);
	signal(SIGINT, SIG_DFL);
}

void	set_signals(void)
{
	struct sigaction	sigint_sa;
	struct sigaction	sigquit_sa;

//	set_term();
	sigemptyset(&sigint_sa.sa_mask);
	sigemptyset(&sigquit_sa.sa_mask);
	sigquit_sa.sa_handler = &sigquit_handler;
	sigint_sa.sa_handler = &sigint_handler;
	sigaction(SIGQUIT, &sigquit_sa, NULL);
	sigaction(SIGINT, &sigint_sa, NULL);
}
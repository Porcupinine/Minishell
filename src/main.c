/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 17:23:55 by laura         #+#    #+#                 */
/*   Updated: 2023/07/17 17:24:47 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include "../Lib42/include/libft.h"
#include "../include/minishell.h"
#include "../include/env_var.h"
#include "../include/lexical_analyzer.h"
#include "../include/token_list_actions.h"
#include "../../include/builtins.h"

int g_exit_code;

void	sigint_handler(int sig)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	kill(0, SIGQUIT);
//	//TODO TOP changes the signal, it can b
//	// reak minishell
}

// if (!isatty(STDIN_FILENO))
//      rl_outstream = stdin;

void	sigquit_handler(int sig)
{
//	rl_on_new_line();
//	rl_replace_line("", 0);
//	rl_redisplay();
}

void set_signals(void)
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

int	main(int argc, char **argv, char **envp)
{
	t_data				*mini_data;

	mini_data = ft_calloc(1, sizeof(t_data));
	if (mini_data == NULL)
		ft_error("Data malloc fail!\n");
	mini_data->mini_envp = envp;//TODO malloc this
	set_signals();
	if (argc != 1)
		ft_error("EROOR!!\nWrong amount of args!\n");
	while (1)
	{
		mini_data->command_line = readline("minisomething: ");
		line_history(mini_data);
		parse_machine(mini_data);
		printf("Exit code: %d\n", g_exit_code);
	}
}

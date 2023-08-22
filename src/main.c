/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmaessen <dmaessen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 17:23:55 by laura         #+#    #+#                 */
/*   Updated: 2023/08/16 14:35:04 by lpraca-l      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <termios.h>
#include "../Lib42/include/libft.h"
#include "../include/minishell.h"
#include "../include/env_var.h"
#include "../include/lexical_analyzer.h"
#include "../include/utils.h"
#include "../include/builtins.h"
#include "../include/exec.h"

int g_exit_code;

void	return_prompt(void)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

//void	sigint_handler(int sig)
//{
//	return_prompt();
//	kill(0, SIGQUIT);
//	//TODO TOP changes the signal, it can break minishell
//}
//
//// if (!isatty(STDIN_FILENO))
////      rl_outstream = stdin;
//
//void	sigquit_handler(int sig)
//{
////	rl_on_new_line();
////	rl_replace_line("", 0);
////	rl_redisplay();
//}
//void
//void	set_signals(void)
//{
//	struct sigaction	sigint_sa;
//	struct sigaction	sigquit_sa;
//	struct termios term;
////
//	tcgetattr(fileno(stdin), &term);
//	sigemptyset(&sigint_sa.sa_mask);
//	sigemptyset(&sigquit_sa.sa_mask);
//	sigquit_sa.sa_handler = &sigquit_handler;
//	sigint_sa.sa_handler = &sigint_handler;
//	sigaction(SIGQUIT, &sigquit_sa, NULL);
//	sigaction(SIGINT, &sigint_sa, NULL);
//	term.c_lflag &= ~ECHOCTL;
//	tcsetattr(fileno(stdin), 0, &term);
//
//}

int	main(int argc, char **argv, char **envp)
{
	t_data				*mini_data;

	mini_data = ft_calloc(1, sizeof(t_data));
	if (mini_data == NULL)
		ft_error("Data malloc fail!\n");
	parse_array_envp(mini_data, envp);
	// parse_list_envp(mini_data, envp);
//	set_signals();
	if (argc != 1)
		ft_error("EROOR!!\nWrong amount of args!\n");
	mini_data->command_line = ft_calloc(1, sizeof(char));
	if (mini_data->command_line == NULL)
		ft_error("Malloc fail \n");
	while (1)
	{
		set_signals();
		mini_data->command_line = readline("MINISHELL: ");
		if (ft_strncmp(mini_data->command_line, "",1) != 0)
		{
			line_history(mini_data);
			parse(mini_data);
			start(mini_data);
		}
//		printf("Exit code: %d\n", g_exit_code);
	}
	return (0);
}

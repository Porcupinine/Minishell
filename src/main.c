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
#include "../include/parser.h"
#include "../include/lexical_analyzer.h"
#include "../include/tolken_list_actions.h"

void	sigint_handler(int sig)
{
	write(1, "sigint\n", 7);
	//TODO TOP changes the signal, it can break minishell
}

// if (!isatty(STDIN_FILENO))
//      rl_outstream = stdin;

void	sigquit_handler(int sig)
{

}

int	main(int argc, char **argv, char **envp)
{
	struct sigaction	sigint_sa;
	struct sigaction	sigquit_sa;
	t_data				*mini_data;

	mini_data = ft_calloc(1, sizeof(t_data));
	if (mini_data == NULL)
		ft_error("Data malloc fail!\n");
	mini_data->mini_envp = envp;
	sigquit_sa.sa_handler = &sigquit_handler;
	sigint_sa.sa_handler = &sigint_handler;
	if (argc != 1)
		ft_error("EROOR!!\nWrong amount of args!\n");
	sigaction(SIGQUIT, &sigquit_sa, NULL);
	sigaction(SIGINT, &sigint_sa, NULL);
	while (1)
	{
		mini_data->command_line = readline("\nminisomething: ");
//        printf("%s\n", mini_data->command_line);
//        count_args(mini_data);
		parse_machine(mini_data);
	}
}

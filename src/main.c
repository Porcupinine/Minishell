/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmaessen <dmaessen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 17:23:55 by laura         #+#    #+#                 */
/*   Updated: 2023/09/04 14:12:16 by lpraca-l      ########   odam.nl         */
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

void	return_prompt(void)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int argc, char **argv, char **envp)
{
	t_data				*mini_data;

	(void)argv;
	mini_data = ft_calloc_exit(1, sizeof(t_data));
	parse_array_envp(mini_data, envp);
	if (argc != 1)
		ft_error("EROOR!!\nWrong amount of args!\n");
	while (1)
	{
		set_signals();
		mini_data->command_line = readline("MINISHELL: ");
		line_history(mini_data);
		if (ft_strncmp(mini_data->command_line, "", 1) != 0)
		{
			if (parse(mini_data) == 0)
				start(mini_data);
		}
	}
	printf("hi\n");
	free(mini_data->command_line);
	free(mini_data);
	return (0);
}

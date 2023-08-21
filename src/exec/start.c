/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 12:48:10 by dmaessen          #+#    #+#             */
/*   Updated: 2023/08/21 16:44:44 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../include/I_want_to_break_free.h"
#include "../../Lib42/include/libft.h"
#include <sys/wait.h>

extern int g_exit_code;

static void multiple_cmd(t_data *mini)
{
	mini->fd = open_pipes(mini);
	exec_fork(mini, mini->nb_cmds); // check if a success
	// if (exec_fork(mini, mini->nb_cmds) == errno) // check
	// 	return (errno); // check what to return here, maybe just 1
	free_pid_list(&mini->process);
	mini->process = NULL;
}

static void one_cmd(t_data *mini)
{
	char **command;

	command = ft_split(mini->commands->cmd, ' ');
	if (!command)
		ft_error("Malloc failed\n");
	mini->fd = open_pipes(mini);
	if (mini->fd == NULL)
		err_msg("", "pipe opening failed.\n"); // check
	if (check_builtins(command, mini) == 1) // so not a builtin
	{
		free_str(command);
		exec_fork_onecmd(mini);
		free_pid_list(&mini->process);
		mini->process = NULL;
	}
	else 
	{
		free_str(command);
		run_one_cmd(mini);
		close_pipe(mini->fd, mini->nb_cmds);
		free_fd(mini->fd, mini->nb_cmds);
		close_fds(mini); // only place i need it right??
	}
}

int	start(t_data *mini)
{
	mini->nb_cmds = lst_size(mini->commands);
	if (mini->nb_cmds == 1 && !mini->commands->cmd) 
	{
		input_re(mini->commands, mini); // error checking
		output_re(mini->commands); // error checking 
		close_fds(mini);
	}
	else if (mini->nb_cmds == 1)
		one_cmd(mini);
	else
		multiple_cmd(mini);
	free_cmd_list(&mini->commands);
	mini->commands = NULL;
	if (access("tmp_file", F_OK) == 0) // does this work?
		unlink("tmp_file");
	return (0);
}


/*
	TO WORK ON:
		-- fork even with one command --> DONE
		-- rework the whole child process to create one for all --> DONE
		-- go through all the builtins
			-- ++ send double pointer to cd and exit
			-- rework cd (its all broke..)
			-- add mini to exit
		-- adapt the location to find $? --> WE LEAVE AS IS FOR NOW
		-- check and change all the error functions
		-- add the right exit_code everywhere 
			-- rm g_exit_code
	
*/
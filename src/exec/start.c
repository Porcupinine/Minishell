/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 12:48:10 by dmaessen          #+#    #+#             */
/*   Updated: 2023/08/30 17:04:25 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../include/utils.h"
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

static void	one_cmd(t_data *mini)
{
	char	**command;

	command = ft_split(mini->commands->cmd, ' ');
	if (check_builtins(command) == 1)
	{
		mini->fd = open_pipes(mini);
		if (mini->fd == NULL)
			err_msg("", "pipe opening failed.\n"); // check
		free_str(command);
		exec_fork_onecmd(mini);
		free_pid_list(&mini->process);
		mini->process = NULL;
	}
	else
	{
		free_str(command);
		input_re(mini->commands, mini);
		output_re(mini->commands);
		if (mini->commands->out < 0 || mini->commands->in < 0)
		{
			set_exit_code(mini, 1);
			close_fds(mini);
			return ;
		}
		split_args(mini->commands->cmd, mini->mini_envp, mini);
		// close_pipe(mini->fd, mini->nb_cmds);
		// free_fd(mini->fd, mini->nb_cmds);
		close_fds(mini);
	}
}

int	start(t_data *mini)
{
	mini->nb_cmds = lst_size(mini->commands);
	if (mini->nb_cmds == 1 && ft_strlen(mini->commands->cmd) == 0)
	{
		input_re(mini->commands, mini);
		if (mini->commands->in < 0)
			return (set_exit_code(mini, 1), 1);
		output_re(mini->commands);
		if (mini->commands->out < 0)
			return (set_exit_code(mini, 1), 1);
		close_fds(mini);
		set_exit_code(mini, 0);
	}
	else if (mini->nb_cmds == 1)
		one_cmd(mini);
	else
		multiple_cmd(mini);
	free_cmd_list(&mini->commands);
	mini->commands = NULL;
	if (access("tmp_file", F_OK) == 0)
		unlink("tmp_file");
	return (mini->exit_code);
}


/*
	TO WORK ON:
		-- fork even with one command --> DONE
		-- rework the whole child process to create one for all --> DONE
		-- go through all the builtins --> DONE
			-- ++ send double pointer to cd and exit --> DONE
			-- rework cd (its all broke..) --> DONE
			-- add mini to exit --> DONE
		-- adapt the location to find $? --> DONE
		-- look into run minishell inside minishell , increase SHVL each time -->DONE
		-- ./test.sh doesn't run the bash script inside of it -->DONE
		-- check and change all the error functions
		-- add the right exit_code everywhere 
			-- rm g_exit_code
		-- start norminetting
	
*/
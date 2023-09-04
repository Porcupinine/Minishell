/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domi <domi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 11:49:01 by dmaessen          #+#    #+#             */
/*   Updated: 2023/09/04 09:38:14 by domi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../include/utils.h"
#include "../../Lib42/include/libft.h"
#include <sys/wait.h>

int	exec_fork_onecmd(t_data *mini)
{
	pid_t	pid;

	pid = fork();
	pid_lstadd_back(&mini->process, pid);
	if (pid == -1)
		return (err_msg("", "fork failed.\n"),
			set_exit_code(mini, 1), 1);
	if (pid == 0)
	{
		unset_signals();
		run_one_cmd(mini);
	}
	close_pipe(mini->fd, mini->nb_cmds);
	free_fd(mini->fd, mini->nb_cmds);
	waitpid(pid, &mini->exit_code, 0);
	if (WIFEXITED(mini->exit_code))
		mini->exit_code = WEXITSTATUS(mini->exit_code);
	if (WIFSIGNALED(mini->exit_code))
		mini->exit_code = 128 + WTERMSIG(mini->exit_code);
	return (mini->exit_code);
}

static int exec_last_cmd(t_data *mini, t_commands *commands, int read_end)
{
	pid_t	pid;
	
	pid = fork();
	pid_lstadd_back(&mini->process, pid);
	if (pid == -1)
		return (err_msg("", "fork failed.\n"),
			set_exit_code(mini, 1), -1);
	printf("getting here?? cmd = %s\n", commands->cmd);
	if (pid == 0)
	{
		set_signals();
		if (dup2(read_end, STDIN_FILENO) == -1)
			return (err_msg("", "dup2 failed.\n"), set_exit_code(mini, 1), exit(1), -1);
		input_re(commands, mini);
		if (commands->in < 0)
			return (set_exit_code(mini, 1), exit(1), -1); // added exit
		output_re(commands);
		if (commands->out < 0)
			return (set_exit_code(mini, 1), exit(1), -1); // added exit
		if (commands->in != STDIN_FILENO)
		{
			if (dup2(commands->in, STDIN_FILENO) == -1)
				return (err_msg("", "dup2 failed.\n"), set_exit_code(mini, 1), exit(1), -1);
			if (close(commands->in) == -1)
				return (err_msg("", "close failed.\n"), set_exit_code(mini, 1), exit(1), -1);
		}
		if (commands->out != STDOUT_FILENO)
		{
			if (dup2(commands->out, STDOUT_FILENO) == -1)
				return (err_msg("", "dup2 failed.\n"), set_exit_code(mini, 1), exit(1), -1);
			if (close(commands->out) == -1)
				return (err_msg("", "close failed.\n"), set_exit_code(mini, 1), exit(1), -1);
		}
		printf("last one, read end= %d\n", read_end);
		split_args(commands->cmd, mini->mini_envp, mini);
	}
	if (close(read_end) == -1)
		return (err_msg("", "close failed.\n"), set_exit_code(mini, 1), exit(1), -1);
	return (pid);
}

static void exec_child(t_data *mini, t_commands *commands, int read_end, int *p_fd)
{
	if (close(p_fd[0]) == -1)
		return (err_msg("", "close failed.\n"), set_exit_code(mini, 1));
	if (dup2(read_end, STDIN_FILENO) == -1)
			return (err_msg("", "dup2 failed.\n"), set_exit_code(mini, 1));
	if (dup2(p_fd[1], STDOUT_FILENO) == -1)
			return (err_msg("", "dup2 failed.\n"), set_exit_code(mini, 1));
	if (commands->in != STDIN_FILENO)
	{
		if (dup2(commands->in, STDIN_FILENO) == -1)
			return (err_msg("", "dup2 failed.\n"), set_exit_code(mini, 1));
		if (close(commands->in) == -1)
			return (err_msg("", "close failed.\n"), set_exit_code(mini, 1));
	}
	if (commands->out != STDOUT_FILENO)
	{
		if (dup2(commands->out, STDOUT_FILENO) == -1)
			return (err_msg("", "dup2 failed.\n"), set_exit_code(mini, 1));
		if (close(commands->out) == -1)
			return (err_msg("", "close failed.\n"), set_exit_code(mini, 1));
	}
}

static void childchild(t_data *mini, t_commands *commands, int read_end, int *p_fd)
{
	input_re(commands, mini);
	if (commands->in < 0)
		return (set_exit_code(mini, 1), exit(1)); // added exit
	output_re(commands);
	if (commands->out < 0)
		return (set_exit_code(mini, 1), exit(1)); // added exit
	exec_child(mini, commands, read_end, p_fd);
	if (mini->exit_code == 1)
	{
		exit(1); // added exit
		return ;
	}
	split_args(commands->cmd, mini->mini_envp, mini);
	if (close(p_fd[1]) == -1)
		return (err_msg("", "close failed.\n"), set_exit_code(mini, 1));
}

static int closeopen_fds(t_data *mini, int read_end, int *p_fd)
{
	if (close(p_fd[1]) == -1)
		return (err_msg("", "close failed.\n"), set_exit_code(mini, 1), -1);
	if (read_end != STDIN_FILENO)
	{
		if (close(read_end) == -1)
			return (err_msg("", "close failed.\n"), set_exit_code(mini, 1), -1);
	}
	read_end = p_fd[0];
	return (read_end);
}

int	exec_fork(t_data *mini)
{
	pid_t		pid;
	int			p_fd[2];
	int			read_end;
	t_commands	*tmp;
	int status;
	int i;

	tmp = mini->commands;
	read_end = 0;
	i = 1;
	while (tmp->next)
	{
		if (pipe(p_fd) == -1)
			return (err_msg("", "pipe failed.\n"),
				set_exit_code(mini, 1), 1);
		pid = fork();
		pid_lstadd_back(&mini->process, pid);
		if (pid == -1)
			return (err_msg("", "fork failed.\n"),
				set_exit_code(mini, 1), 1);
		if (pid == 0)
		{
			unset_signals();
			childchild(mini, tmp, read_end, p_fd);
			read_end = closeopen_fds(mini, read_end, p_fd);
			if (read_end == -1)
				return (1);
		}
		printf("next\n");
		tmp = tmp->next;
		i++;
	}
	printf("last\n");
	pid = exec_last_cmd(mini, tmp, read_end);
	if (pid != -1)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			mini->exit_code = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			mini->exit_code = 128 + WTERMSIG(status);
		while (1)
			if (wait(NULL) == -1)
				break ;
	}
	printf("returing?\n");
	return (mini->exit_code);
}



// OLD
// int	exec_fork_onecmd(t_data *mini)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	pid_lstadd_back(&mini->process, pid);
// 	if (pid == -1)
// 		return (err_msg("", "fork failed.\n"),
// 			set_exit_code(mini, 1), 1);
// 	if (pid == 0)
// 	{
// 		unset_signals();
// 		run_one_cmd(mini);
// 	}
// 	close_pipe(mini->fd, mini->nb_cmds);
// 	free_fd(mini->fd, mini->nb_cmds);
// 	waitpid(pid, &mini->exit_code, 0);
// 	if (WIFEXITED(mini->exit_code))
// 		mini->exit_code = WEXITSTATUS(mini->exit_code);
// 	if (WIFSIGNALED(mini->exit_code))
// 		mini->exit_code = 128 + WTERMSIG(mini->exit_code);
// 	return (mini->exit_code);
// }

// int	exec_fork(t_data *mini, int nb_cmds)
// {
// 	pid_t		pid;
// 	int			i;
// 	int			pos;
// 	t_commands	*tmp;

// 	tmp = mini->commands;
// 	i = 1;
// 	pos = 0;
// 	while (i <= nb_cmds)
// 	{
// 		pid = fork();
// 		pid_lstadd_back(&mini->process, pid);
// 		if (pid == -1)
// 			return (err_msg("", "fork failed.\n"),
// 				set_exit_code(mini, 1), 1);
// 		if (pid == 0)
// 		{
// 			unset_signals();
// 			child_dup2(mini, tmp, i, pos); // because what happens when it returns here with an error
// 		}
// 		if (i != nb_cmds)
// 			tmp = tmp->next;
// 		i++;
// 		pos++;
// 	}
// 	close_pipe(mini->fd, mini->nb_cmds);
// 	free_fd(mini->fd, mini->nb_cmds);
// 	waitpid(pid, &mini->exit_code, 0);
// 	if (WIFEXITED(mini->exit_code))
// 		mini->exit_code = WEXITSTATUS(mini->exit_code);
// 	if (WIFSIGNALED(mini->exit_code))
// 		mini->exit_code = 128 + WTERMSIG(mini->exit_code);
// 	return (mini->exit_code);
// }

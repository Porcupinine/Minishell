// ADD 42 HEADER

#include "minishell.h"

static void	child_start(int fd_w[], int in_file, t_data *mini) // pointer needed??
{
	if (dup2(in_file, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE); // check
	if (dup2(fd_w[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE); // check
	close(fd_w[0]);
	close(in_file);
	close_pipe(mini->commands->fd, mini->commands->nb_cmds);
	split_args(mini->commands->cmd, mini->mini_envp);
}

static void	child_last(int fd_r[], int out_f, t_pipexb pipex, int pos) // pos to loop to the right node before sending to split_arg
{
	if (dup2(fd_r[0], STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (dup2(out_f, STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(fd_r[1]);
	close(out_f);
	close_pipe(pipex.fd, pipex.argc);
	split_args(pipex.argv[pipex.argc - 2], pipex.envp);
}

static void	child_middle(int fd_r[], int fd_w[], t_pipexb pipex, int pos) // pos to loop to the right node before sending to split_arg
{
	if (dup2(fd_r[0], STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (dup2(fd_w[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(fd_w[0]);
	close(fd_r[1]);
	close_pipe(pipex.fd, pipex.argc);
	split_args(pipex.argv[2 + pipex.index], pipex.envp);
}

void	which_child(t_data *mini, int i, int pos)
{
	if (i == 1 && pos == 0)
		child_start(mini->commands->fd[pos], mini->commands->in, mini); 
	else if (i == mini->commands->nb_cmds)
		child_last(mini->commands->fd[pos - 1], mini->commands->out, mini, pos); // WE WERE HERE
	else
	{
		if (i <= 1024) // think its fine here as you never know if something might break
		{
			pipex.index++;
			child_middle(pipex.fd[pos - 1], pipex.fd[pos], mini, pos);
		}
	}
}
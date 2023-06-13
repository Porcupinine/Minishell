/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:49:22 by dmaessen          #+#    #+#             */
/*   Updated: 2023/06/13 16:14:16 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_start(int fd_w[], int in_file, t_pipexb pipex)
{
	if (dup2(in_file, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (dup2(fd_w[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(fd_w[0]);
	close(in_file);
	close_pipe(pipex.fd, pipex.argc);
	split_args(pipex.argv[2], pipex.envp);
}

static void	child_last(int fd_r[], int out_f, t_pipexb pipex)
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

static void	child_middle(int fd_r[], int fd_w[], t_pipexb pipex)
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

void	which_child(t_pipexb pipex, int i, int pos)
{
	if (i == 2 && pos == 0)
		child_start(pipex.fd[pos], pipex.in_file, pipex);
	else if (i == (pipex.argc - 2))
		child_last(pipex.fd[pos - 1], pipex.out_f, pipex);
	else
	{
		if (pipex.index < 1024) // could this be something ??
		{
			pipex.index++;
			child_middle(pipex.fd[pos - 1], pipex.fd[pos], pipex);
		}
	}
}

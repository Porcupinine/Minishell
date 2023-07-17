/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:58:35 by dmaessen          #+#    #+#             */
/*   Updated: 2023/06/22 16:11:44 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"
#include "../../include/pipes.h"
#include "../../Lib42/include/libft.h"

void	child1(t_pipexb pipex, int fd[])
{
	if (dup2(pipex.in_file, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(fd[0]);
	close(pipex.in_file);
	split_args(pipex.argv[3], pipex.envp);
}

void	child2(t_pipexb pipex, int fd[])
{
	if (dup2(pipex.out_f, STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(fd[1]);
	close(pipex.out_f);
	split_args(pipex.argv[4], pipex.envp);
}

static void	execute_pipe_std(t_pipexb pipex, int fd[]) // use same principle as multi-pipe
{
	pid_t	process1;
	pid_t	process2;

	process1 = fork();
	if (process1 == -1)
		exit(EXIT_FAILURE);
	if (process1 == 0)
		child1(pipex, fd);
	process2 = fork();
	if (process2 == -1)
		exit(EXIT_FAILURE);
	if (process2 == 0)
		child2(pipex, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(process1, &pipex.status, 0);
	waitpid(process2, &pipex.status, 0);
	unlink("tmp_file");
	if (WIFEXITED(pipex.status))
		exit(WEXITSTATUS(pipex.status));
}

int	ft_heredoc(int argc, char *argv[], char *envp[])
{
	t_pipexb	pipex;
	int			fd[2];

	// if (argc != 6)
	// {
	// // 	ft_putstr_fd("Error: invalid number of arguments.\n", 2);
	// // 	exit(EXIT_FAILURE);
	// }
	pipex.in_file = open("tmp_file", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (ft_strncmp(argv[argc - 2], ">>", 2) == 0) // appends to exisiting file or creates it
		pipex.out_f = open(argv[argc - 1], O_APPEND | O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (ft_strncmp(argv[argc - 2], ">", 1) == 0) // overwrites existing file or creates a new one with specified name // makes sense ??
		pipex.out_f = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	// else // output result on the terminal
	if (pipex.in_file < 0 || pipex.out_f < 0) // split this one, out_f might not be in use
		no_perm_err(argc, argv);
	pipex.argc = argc;
	pipex.argv = argv;
	pipex.envp = envp;
	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	read_stdin(pipex);
	close(pipex.in_file);
	pipex.in_file = open("tmp_file", O_RDONLY);
	execute_pipe_std(pipex, fd); // no use the same as as multi-pipe, as could be more than two so doesn't work here
	return (0);
}

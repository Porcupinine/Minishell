/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:19:04 by dmaessen          #+#    #+#             */
/*   Updated: 2023/06/22 16:11:59 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"
#include "../../include/pipes.h"
#include "../../Lib42/include/libft.h"

static int	execute_pipe(t_pipexb pipex)
{
	pid_t	process;
	int		i;
	int		pos;

	i = 2;
	pos = 0;
	while (i < (pipex.argc - 1))
	{
		process = fork();
		if (process == -1)
			return (1);
		if (process == 0)
			which_child(pipex, i, pos);
		i++;
		pos++;
	}
	close_pipe(pipex.fd, pipex.argc);
	free_fd(pipex.fd, pipex.argc);
	close(pipex.in_file);
	close(pipex.out_f);
	waitpid(process, &pipex.status, 0);
	if (WIFEXITED(pipex.status))
		exit(WEXITSTATUS(pipex.status));
	return (0);
}

static int	**open_pipes(int argc)
{
	int		**fd;
	int		nb;
	int		i;

	nb = argc - 4;
	fd = (int **)malloc((nb) * sizeof(int *));
	i = 0;
	while (i < nb)
	{
		fd[i] = (int *)malloc(2 * sizeof(int));
		i++;
	}
	i = 0;
	while (i < nb)
	{
		if (pipe(fd[i]) < 0)
			return (NULL);
		i++;
	}
	return (fd);
}

void	close_pipe(int **fd, int argc)
{
	int	nb;
	int	i;

	nb = argc - 4;
	i = 0;
	while (i < nb)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

void	free_fd(int **fd, int argc)
{
	int	nb;
	int	i;

	nb = argc - 4;
	i = 0;
	while (i < nb)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipexb	pipex;

	// any invalide nb of arg possible ??
	// that check will be done during paser so here we assume argc is valid
	if (ft_strncmp(argv[1], "<<", 2) == 0) // instead of here_doc, add more changes to know the "LIMITER"
		ft_heredoc(argc, argv, envp); // don't think the above should be the condition tho
		// check for > OR >> (OR nothing at all?) for the closing part, like where to write to right??
	else // implying (ft_strncmp(argv[1], "<", 1) == 0)
	{
		pipex.in_file = open(argv[1], O_RDONLY); // if any ..
		pipex.out_f = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (pipex.in_file < 0 || pipex.out_f < 0)
			no_perm_err(argc, argv);
		pipex.argc = argc;
		pipex.argv = argv;
		pipex.envp = envp;
		pipex.index = 0;
		pipex.fd = open_pipes(argc);
		if (pipex.fd == NULL)
			exit(EXIT_FAILURE);
		if (execute_pipe(pipex) == 1)
			exit(EXIT_FAILURE);
	}
	// other version needed without in and out files OR could we make a rule depending on < << >> > ??
}

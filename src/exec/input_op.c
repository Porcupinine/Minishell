/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:19:42 by dmaessen          #+#    #+#             */
/*   Updated: 2023/07/21 16:57:00 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
    for the input operators sorting out
        use case for <
            read from file that comes after 
            O_RDONLY
            F_OK ??
        use case for <<
            redirect input to stdin until LIMITER
            --> maybe something for Laura to deal with tho and pass me on the input
        use case with nothin ?

    QUESTION
        can we have multiple after one another??

*/

#include "minishell.h"

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

bool	dollar_check(t_data *mini)
{
	bool 	quotes;
	int		s_quote;
	int		d_quote;
	int		i;
	
	i = 0;
	s_quote = 0;
	d_quote = 0;
	quotes = false;
	while (mini->commands->infiles->file[i])
	{
		if (mini->commands->infiles->file[i] == )
		i++;
	}
}

static void	free_stdin(char *line, char *str)
{
	free(line);
	free(str);
}

static char	*rm_newline(char *line, char *limiter)
{
	size_t	len;
	char	*sub;

	if (line == NULL)
		return (NULL);
	len = ft_strlen(line);
	if (ft_strchr(line, '\n') == NULL || ft_strncmp(limiter, "\n", 2) == 0)
		sub = ft_substr(line, 0, len + 1);
	else
		sub = ft_substr(line, 0, len);
	return (sub);
}

void    read_stdin(t_data *mini)
{
	char	*line;
	char	*limiter;
	char	*str;
	int		i;
	bool	quotes;

	limiter = mini->commands->infiles->file;
	quotes = dollar_check(mini);
		// needs to expand $ARG, but what are the edgecases??
			// if ARG doesn't exist then replace with blank (not even a space)
			// expands if: word on its own
			// doesn't expand if: we have two single/double quotes in in the word; if only one then unclosed quote then what??
	line = get_next_line_exit(0); // check if its the correct gnl
	str = rm_newline(line, limiter);
	while (line != NULL && ft_strncmp(str, limiter, ft_strlen(limiter)) != 0)
	{
		i = ft_strlen(line);
		write(mini->commands->in, line, i);
		if (ft_strchr(line, '\n') == NULL)
			break ;
		free_stdin(line, str);
		line = get_next_line_exit(0); // check if its the correct gnl
		if (line == NULL)
			break ;
		str = rm_newline(line, limiter);
	}
	if (line != NULL && str != NULL)
		free_stdin(line, str);
}

void input_re(t_data *mini)
{
    if (mini->commands->infiles->file == NULL) // meaning no infile
		mini->commands->in = STDIN_FILENO;
    else if (mini->commands->infiles->file->type == heredoc)
    {
		mini->commands->in = open("tmp_file", O_CREAT | O_WRONLY | O_TRUNC, 0644); // or name it heredoc??
        read_stdin(mini);
        close(mini->commands->in);
        mini->commands->in = open("tmp_file", O_RDONLY); // or name it heredoc??
    }
    else
        mini->commands->in = open(mini->commands->infiles->file, O_RDONLY, 0644);
	if (mini->commands->in < 0)
		// through an error -- no perm error
}
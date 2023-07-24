/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:19:42 by dmaessen          #+#    #+#             */
/*   Updated: 2023/07/24 14:58:14 by dmaessen         ###   ########.fr       */
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

static bool	dollar_check(t_data *mini)
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
		if (mini->commands->infiles->file[i] == 34) // single quote
			s_quote += 1;
		if (mini->commands->infiles->file[i] == 39) // double quote
			d_quote += 1;
		i++;
	}
	if (s_quote % 2 == 0) // so they're in pair
		quotes = true;
	if (s_quote % 2 == 0) // so they're in pair
		quotes = true;
	return (quotes);
}

static char	*find_arg(char *arg, t_data *mini)
{
	int	i;
	char *new;

	i = 0;
	arg = ft_strtrim(arg, '$');
	while (mini->mini_envp[i])
	{
		if (ft_strncmp(mini->mini_envp[i], arg, ft_strlen(arg)) == 0)
		{
			new = ft_strtrim(mini->mini_envp[i], arg); // do i need to protect this thing?? or free??
			break ;
		}
		i++;
	}
	if (new == NULL)
	{
		while (mini->env_args != NULL) // or is the ->next pointing to NULL ??
		{
			if (ft_strncmp(mini->env_args, arg, ft_strlen(arg)) == 0)
			{
				new = ft_strtrim(mini->env_args, arg); // do i need to protect this thing?? or free??
				break ;
			}
			mini->env_args = mini->env_args->next;
		}
	}
	if (new == NULL) // if ARG doesn't exist then replace with blank (not even a space)
		new[0] = '\0'; // meaning just nothing, right??
	return (new);
}

char *expand_dollar(char *line, t_data *mini)
{
	int i;
	int len;
	int dollar; // maybe put this count in an ft
	int d;
	char *arg; // to store he expantion
	char *new;

	i = 0;
	dollar = 0;
	while (line[i])
	{
		if (line[i] == '$')
			dollar++;
		i++;
	}
	d = 0;
	while (d < dollar)
	{
		i = 0;
		len = 0;
		while (line[i])
		{
			if (line[i] == '$')
			{
				while (line[i] != ' ')
				{
					arg[len] = line[i];
					len++;
					i++;
				}
			new = find_arg(arg, mini); // search in path and local and store the expantion
			ft_strlcat(line[i - len], new, ft_strlen(new)); // is this len correct??
			free_stdin(new, arg);
			}
			i++;
		}
		d++;
	}
	return (line);
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
	line = get_next_line_exit(0); // check if its the correct gnl
	str = rm_newline(line, limiter);
	while (line != NULL && ft_strncmp(str, limiter, ft_strlen(limiter)) != 0)
	{
		if (quotes == false)
		 	line = expand_dollar(line, mini);
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
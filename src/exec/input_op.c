/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:19:42 by dmaessen          #+#    #+#             */
/*   Updated: 2023/07/31 14:53:18 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"

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
static char *trim_limiter(t_data *mini)
{
	int		i;
	int		j;
	char	*trim;

	i = 0;
	j = 0;
	while (mini->commands->infiles->file[i])
	{
		if (mini->commands->infiles->file[i] != 34
			&& mini->commands->infiles->file[i] != 39)
			trim[j] = mini->commands->infiles->file[i];
		i++;
		j++;
	}
	trim[j] = '\0'; // needed??
	return (trim);
}

static char	*find_arg(char *arg, t_data *mini) // what am i doing, actually not doing with this function??
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
	// if (ft_strchr(line, "\\n") == NULL) // no we do not need to deal with this
	// 	line = ft_strtrim(line, "\\n"); // so it also rm that last backslash right??
	// 		// does this trim need protection or not??
	len = ft_strlen(line);
	if (ft_strchr(line, '\n') == NULL || ft_strncmp(limiter, "\n", 2) == 0)
		sub = ft_substr(line, 0, len + 1);
	else
		sub = ft_substr(line, 0, len);
	return (sub);
}

void	read_stdin(t_data *mini)
{
	char	*line;
	char	*limiter;
	char	*str;
	int		i;
	bool	quotes;

	quotes = false;
	if (ft_strchr(mini->commands->infiles->file, '"') != 0
		|| ft_strchr(mini->commands->infiles->file, '\'') != 0)
		quotes = true;
	limiter = trim_limiter(mini); // no harm doing this check
	line = get_next_line_exit(0); // check if its the correct gnl
	str = rm_newline(line, limiter); // check if picks up the backslash
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
    if (mini->commands->infiles->file == NULL)
		mini->commands->in = NULL; // check
    else if (mini->commands->infiles->file->type == heredoc)
    {
		mini->commands->in = open("tmp_file", O_CREAT | O_WRONLY | O_TRUNC, 0644);
        read_stdin(mini);
        close(mini->commands->in);
        mini->commands->in = open("tmp_file", O_RDONLY);
    }
    else
        mini->commands->in = open(mini->commands->infiles->file, O_RDONLY, 0644);
	if (mini->commands->in < 0)
		// throw an error -- no perm error
}
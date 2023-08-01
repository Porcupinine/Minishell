/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domi <domi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:19:42 by dmaessen          #+#    #+#             */
/*   Updated: 2023/08/01 19:54:19 by domi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"

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
	limiter = trim_limiter(mini);
	line = get_next_line_fd(STDIN_FILENO); // correct gnl?
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
		line = get_next_line_fd(STDIN_FILENO); // check if its the correct gnl
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
    else if (mini->commands->infiles->file->type == HEREDOC)
    {
		mini->commands->in = open("tmp_file", O_CREAT | O_WRONLY | O_TRUNC, 0644);
        read_stdin(mini);
        close(mini->commands->in);
        mini->commands->in = open("tmp_file", O_RDONLY);
    }
    else
        mini->commands->in = open(mini->commands->infiles->file, O_RDONLY, 0644);
	if (mini->commands->in < 0)
		builtin_err(mini->commands->infiles->file, "No such file or directory"); // return?
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:19:42 by dmaessen          #+#    #+#             */
/*   Updated: 2023/08/07 17:29:13 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"
#include "../../Lib42/include/get_next_line.h"

static char *trim_limiter(t_commands *commands)
{
	int		i;
	int		j;
	char	*trim;

	trim = ft_calloc(ft_strlen(commands->infiles->file), 1);
	if (trim == NULL)
		return (ft_error("Malloc failed.\n"), NULL); // check
	i = 0;
	j = 0;
	while (commands->infiles->file[i])
	{
		if (commands->infiles->file[i] != 34
			&& commands->infiles->file[i] != 39)
			trim[j] = commands->infiles->file[i];
		i++;
		j++;
	}
	return (trim); // needs to be freed later??
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

void	read_stdin(t_commands *commands, t_data *mini)
{
	char	*line;
	char	*limiter;
	char	*str;
	int		i;
	bool	quotes;

	quotes = false;
	if (ft_strchr(commands->infiles->file, '"') != 0
		|| ft_strchr(commands->infiles->file, '\'') != 0)
		quotes = true;
	limiter = trim_limiter(commands);
	line = get_next_line_fd(0); // correct gnl?
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
		line = get_next_line_fd(0); // check if its the correct gnl
		if (line == NULL)
			break ;
		str = rm_newline(line, limiter);
	}
	if (line != NULL && str != NULL)
		free_stdin(line, str);
}

static void handle_heredoc(t_commands *commands, t_data *mini)
{
	commands->in = open("tmp_file", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	read_stdin(commands, mini);
	close(commands->in);
	commands->in = open("tmp_file", O_RDONLY);
}

void input_re(t_commands *commands, t_data *mini)
{
    if (commands->infiles->file == NULL)
		commands->in = STDIN_FILENO; // test this
		// commands->in = NULL; // check
	while (commands->infiles)
	{
		if (commands->infiles->type == HEREDOC)
			handle_heredoc(commands, mini);
		else
			commands->in = open(commands->infiles->file, O_RDONLY, 0644);
		if (commands->in < 0)
		{
			builtin_err(commands->infiles->file, "No such file or directory"); // return?
			break ; // right??
		}
		if (commands->infiles->next != NULL)
			close(commands->in);
		commands->infiles = commands->infiles->next;
	}
}

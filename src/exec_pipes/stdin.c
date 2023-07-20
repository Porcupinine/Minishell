/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:03:07 by dmaessen          #+#    #+#             */
/*   Updated: 2023/06/22 16:12:10 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/pipes.h"
#include "../../Lib42/include/libft.h"

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

void	read_stdin(t_pipexb pipex)
{
	char	*line;
	char	*limiter;
	char	*str;
	int		i;

	limiter = pipex.argv[2]; // check for double quotes here // is this true?? just word after oeprator
	line = get_next_line(0);
	str = rm_newline(line, limiter);
	while (line != NULL && ft_strncmp(str, limiter, ft_strlen(limiter)) != 0)
	{
		i = ft_strlen(line);
		write(pipex.in_file, line, i);
		if (ft_strchr(line, '\n') == NULL)
			break ;
		free_stdin(line, str);
		line = get_next_line(0);
		if (line == NULL)
			break ;
		str = rm_newline(line, limiter);
	}
	if (line != NULL && str != NULL)
		free_stdin(line, str);
}

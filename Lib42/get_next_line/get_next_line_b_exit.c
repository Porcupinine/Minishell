/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_b_exit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 08:08:19 by dmaessen          #+#    #+#             */
/*   Updated: 2023/08/02 08:08:23 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

void	ft_free_b(char **memory, char *line)
{
	free(*memory);
	*memory = NULL;
	free(line);
}

static char	*current_line(char *memory)
{
	size_t	i;
	char	*line;

	i = 0;
	while (memory[i] != '\0' && memory[i] != '\n')
		i++;
	if (memory[i] == '\n')
		i++;
	line = ft_substr_gnl_b(memory, 0, i);
	if (!line)
		return (free(line), NULL);
	return (line);
}

static char	*sub_mem(char *memory)
{
	size_t	i;
	size_t	len;
	char	*sub;

	i = 0;
	len = ft_strlen_gnl(memory);
	while (memory[i] != '\0' && memory[i] != '\n')
		i++;
	if (memory[i] == '\n')
		i++;
	if (!memory[i])
		return (free(memory), NULL);
	sub = ft_substr_gnl_b(memory, i, len - i);
	if (!sub)
		return (ft_free_b(&memory, NULL), ft_error("Malloc fail\n"), NULL); // TODO malloc exit fine like this?
	free(memory);
	return (sub);
}

static char	*reading(int fd, char *memory)
{
	int		nbyte;
	char	*buf;

	buf = ft_calloc_b((BUFFER_SIZE + 1), sizeof(char));
	if (!buf)
		return (free(memory), ft_error("Malloc fail\n"), NULL); // TODO malloc exit fine like this?
	nbyte = 1;
	while (nbyte != 0 && !ft_strchr_gnl_b(memory, '\n'))
	{
		nbyte = read(fd, buf, BUFFER_SIZE);
		if (nbyte < 0)
			return (ft_free_b(&memory, buf), NULL);
		buf[nbyte] = '\0';
		memory = ft_strjoin_gnl_b(memory, buf);
		if (!memory)
			return (ft_free_b(&memory, buf), NULL);
	}
	free (buf);
	return (memory);
}

char	*get_next_line_fd(int fd)
{
	static char	*memory;
	char		*newline;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147483647)
		return (NULL);
	if (!memory)
	{
		memory = ft_calloc_b(1, 1);
		if (!memory)
			return (ft_error("Malloc fail\n"), NULL); // TODO malloc exit fine like this?
	}
	memory = reading(fd, memory);
	if (!memory)
		return (free(memory), NULL);
	newline = current_line(memory);
	if (!newline)
		return (ft_free_b(&memory, NULL), NULL);
	memory = sub_mem(memory);
	return (newline);
}
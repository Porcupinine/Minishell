/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_b_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 08:08:33 by dmaessen          #+#    #+#             */
/*   Updated: 2023/08/02 08:08:35 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_gnl_b(char *memory, char *buf)
{
	size_t	i;
	size_t	len1;
	char	*join;

	if (!*memory && !*buf)
		return (free(memory), NULL);
	len1 = (ft_strlen_gnl(memory));
	join = ft_calloc_b((len1 + ft_strlen_gnl(buf) + 1), sizeof(char));
	if (!join)
		return (ft_free_b(&memory, NULL), ft_error("Malloc fail\n"), NULL); // TODO malloc exit fine like this?
	i = 0;
	while (memory[i])
	{
		join[i] = memory[i];
		i++;
	}
	i = 0;
	while (buf[i])
	{
		join[len1 + i] = buf[i];
		i++;
	}
	join[len1 + ft_strlen_gnl(buf)] = '\0';
	return (free(memory), join);
}

char	*ft_strchr_gnl_b(const char *s, int c)
{
	int		i;
	char	*str;

	if (!s)
		return (NULL);
	str = (char *)s;
	i = 0;
	while (s[i] && s[i + 1] && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		return (&str[i + 1]);
	return (NULL);
}

void	*ft_calloc_b(size_t count, size_t size)
{
	size_t	i;
	char	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}

char	*ft_substr_gnl_b(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;

	if (!s)
		return (NULL);
	if (ft_strlen_gnl(s) < (int)start)
	{
		sub = malloc(1 * sizeof(char));
		if (!sub)
			return (ft_error("Malloc fail\n"), NULL); // TODO malloc exit fine like this?
		sub[0] = '\0';
		return (sub);
	}
	sub = malloc((len + 1) * sizeof(char));
	if (!sub)
		return (ft_error("Malloc fail\n"), NULL); // TODO malloc exit fine like this?
	i = 0;
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

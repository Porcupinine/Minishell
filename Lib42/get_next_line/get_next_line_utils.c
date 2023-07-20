/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lpraca-l <lpraca-l@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/04 19:18:41 by lpraca-l      #+#    #+#                 */
/*   Updated: 2023/01/23 17:35:16 by lpraca-l      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_gnl(const char *c)
{
	long	count;

	count = 0;
	while (c[count] != '\0')
		count++;
	return (count);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2, long buff_len_to_get)
{
	long		counts1;
	char		*join;
	long		len;
	long		counts2;

	counts1 = 0;
	counts2 = 0;
	len = ft_strlen_gnl(s1) + buff_len_to_get;
	join = malloc((len + 1) * sizeof(char));
	if (join == NULL)
		return (NULL);
	while (s1[counts1] != '\0')
	{
		join[counts1] = s1[counts1];
		counts1++;
	}
	while (counts2 < buff_len_to_get)
	{
		join[counts1] = s2[counts2];
		counts1++;
		counts2++;
	}
	join[counts1] = '\0';
	return (join);
}

char	*ft_strlcpy_gnl(const char	*src, long dst_size)
{
	long	count;
	char	*alias;
	char	*dst;

	alias = (char *) src;
	count = 0;
	dst = malloc((dst_size + 1) * sizeof(char));
	if (dst == NULL)
		return (NULL);
	while (count < dst_size)
	{
		dst[count] = alias[count];
		count++;
	}
	dst[count] = '\0';
	return (dst);
}

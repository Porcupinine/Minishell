/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:05:14 by lpraca-l          #+#    #+#             */
/*   Updated: 2023/08/30 14:00:57 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	strlcpy() and strlcat() functions copy and concatenate strings with
     the same input parameters and output result as snprintf(3).  They are
     designed to be safer, more consistent, and less error prone replacements
     for the easily misused functions strncpy(3) and strncat(3).

     strlcpy() and strlcat() take the full size of the destination buffer and
     guarantee NUL-termination if there is room.  Note that room for the NUL
     should be included in dstsize.

     strlcpy() copies up to dstsize - 1 characters from the string src to dst,
     NUL-terminating the result if dstsize is not 0.

     If the src and dst strings overlap, the behavior is undefined.
	 return the total length of the string they tried to createmake */

#include "libft.h"

size_t	ft_strlcpy(char	*dst, const char *src, size_t dstsize)
{
	size_t	count;
	char	*alias;

	alias = (char *) src;
	count = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (count < (dstsize -1) && alias[count] != '\0')
	{
		dst[count] = alias[count];
		count++;
	}
	dst[count] = '\0';
	return (ft_strlen(src));
}

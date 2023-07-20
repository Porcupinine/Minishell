/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lpraca-l <lpraca-l@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/29 11:55:50 by lpraca-l      #+#    #+#                 */
/*   Updated: 2022/10/29 12:06:10 by lpraca-l      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*The memchr() function locates the first occurrence of c (converted to an
     unsigned char) in string s.
	The memchr() function returns a pointer to the byte located, or NULL if
     no such byte exists within n bytes.
*/

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			count;
	unsigned char	*alias;
	unsigned char	alias_search;

	alias = (unsigned char *)s;
	count = 0;
	alias_search = (unsigned char)c;
	while (count < n)
	{
		if (alias[count] == alias_search)
			return (alias + count);
		count++;
	}
	return (NULL);
}

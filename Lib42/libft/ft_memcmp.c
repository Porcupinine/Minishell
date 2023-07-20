/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lpraca-l <lpraca-l@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 19:10:01 by lpraca-l      #+#    #+#                 */
/*   Updated: 2022/10/22 13:06:15 by lpraca-l      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*The memcmp() function compares byte string s1 against byte string s2.
     Both strings are assumed to be n bytes long.
	 The memcmp() function returns zero if the two strings are identical, oth-
     erwise returns the difference between the first two differing bytes
     (treated as unsigned char values, so that `\200' is greater than `\0',
     for example).  Zero-length strings are always identical.  This behavior
     is not required by C and portable code should only depend on the sign of
     the returned value */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*alias1;
	unsigned char	*alias2;
	size_t			count;

	count = 0;
	alias1 = (unsigned char *) s1;
	alias2 = (unsigned char *) s2;
	while (count < n)
	{
		if (alias1[count] == alias2[count])
			count++;
		else
			return (alias1[count] - alias2[count]);
	}
	if (count < n)
		return (alias1[count] - alias2[count]);
	return (0);
}

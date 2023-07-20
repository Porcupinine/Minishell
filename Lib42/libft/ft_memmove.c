/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lpraca-l <lplacerdadesign@gmail.com>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/08 17:08:54 by lpraca-l      #+#    #+#                 */
/*   Updated: 2022/10/22 11:04:43 by lpraca-l      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*The memmove() function copies n bytes from memory area src to
memory area dest.The memory areas may overlap:copying takes place as though 
the bytes in src are first copied into a temporary array that does  not  overlap
src or dest, and the bytes are then copied from the temporary array to dest.
The memmove() function returns a pointer to dest.*/

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*alias_d;
	const char	*alias_s;

	alias_d = dest;
	alias_s = src;
	if (alias_d == NULL && alias_s == NULL)
		return (0);
	if (alias_d > alias_s)
	{
		while (n > 0)
		{
			alias_d[n - 1] = alias_s[n - 1];
			n--;
		}
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}

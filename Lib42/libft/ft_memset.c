/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lpraca-l <lplacerdadesign@gmail.com>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/08 16:24:06 by lpraca-l      #+#    #+#                 */
/*   Updated: 2022/10/09 21:52:09 by lpraca-l      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*The memset() function fills the first n bytes of the memory area pointed to 
by s with the constant byte c.
The memset() function returns a pointer to the memory area s.*/

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	count;
	char	*alias;

	alias = s;
	count = 0;
	while (count < n)
	{
		alias[count] = c;
		count++;
	}
	return (s);
}

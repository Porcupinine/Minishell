/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lpraca-l <lplacerdadesign@gmail.com>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/08 16:19:41 by lpraca-l      #+#    #+#                 */
/*   Updated: 2022/10/21 16:39:20 by lpraca-l      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*The strlen() function calculates the length of the string pointed to by s, 
excluding the terminating null byte ('\0').
The strlen() function returns the number of bytes in the string pointed to by s.
*/

#include "libft.h"

size_t	ft_strlen(const char *c)
{
	size_t	count;

	count = 0;
	while (c[count] != '\0')
	{
		count++;
	}
	return (count);
}

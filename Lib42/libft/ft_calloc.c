/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lpraca-l <lpraca-l@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 12:53:41 by lpraca-l      #+#    #+#                 */
/*   Updated: 2022/10/21 17:51:59 by lpraca-l      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*The calloc() function contiguously allocates enough space for count
     objects that are size bytes of memory each and returns a pointer to the
     allocated memory.  The allocated memory is filled with bytes of value
     zero.
	 If successful, calloc(), malloc(), realloc(), reallocf(), and valloc()
     functions return a pointer to allocated memory.  If there is an error,
     they return a NULL pointer and set errno to ENOMEM.*/

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*call;

	call = malloc(count * size);
	if (call == NULL)
		return (NULL);
	ft_bzero(call, (count * size));
	return (call);
}

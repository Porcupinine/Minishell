/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lpraca-l <lpraca-l@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 13:46:12 by lpraca-l      #+#    #+#                 */
/*   Updated: 2022/10/21 15:44:44 by lpraca-l      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*The strdup() function allocates sufficient memory for a copy of the
     string s1, does the copy, and returns a pointer to it.  The pointer may
     subsequently be used as an argument to the function free(3).

     If insufficient memory is available, NULL is returned and errno is set to
     ENOMEM.
*/

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;
	int		count;

	count = 0;
	dup = malloc((ft_strlen(s1) + 1) * (sizeof(char)));
	if (dup == NULL)
		return (NULL);
	while (s1[count] != '\0')
	{
		dup[count] = s1[count];
		count++;
	}
	dup[count] = '\0';
	return (dup);
}

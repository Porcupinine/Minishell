/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lpraca-l <lpraca-l@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 14:14:55 by lpraca-l      #+#    #+#                 */
/*   Updated: 2022/10/31 18:32:41 by lpraca-l      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*Allocates (with malloc(3)) and returns a substring from the string ’s’.
The substring begins at index ’start’ and is ofmaximum size ’len’.
Returns The substring or NULL if the allocation fails.*/

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;
	size_t	final_string_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (start > s_len)
		final_string_len = 0;
	else
		final_string_len = s_len - start;
	if (final_string_len > len)
		final_string_len = len;
	sub = ft_calloc_exit((final_string_len + 1), sizeof(char));
	ft_strlcpy(sub, &(s[start]), final_string_len + 1);
	return (sub);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 21:24:49 by lpraca-l          #+#    #+#             */
/*   Updated: 2023/08/25 11:29:31 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*The strncmp() function compares not more than n characters.  Because
     strncmp() is designed for comparing strings rather than binary data,
     characters that appear after a `\0' character are not compared.
	 The strcmp() and strncmp() functions return an integer greater than,
     equal to, or less than 0, according as the string s1 is greater than,
     equal to, or less than the string s2.  The comparison is done using
     unsigned characters, so that `\200' is greater than `\0'.*/

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*alias1;
	unsigned char	*alias2;
	size_t			count;

	alias1 = (unsigned char *) s1;
	alias2 = (unsigned char *) s2;
	count = 0;
	while (alias1[count] != '\0' && alias2[count] != '\0' && count < n)
	{
		if (alias1[count] == alias2[count])
			count++;
		else
			return (alias1[count] - alias2[count]);
	}
	if (count != n)
		return (alias1[count] - alias2[count]);
	return (0);
}

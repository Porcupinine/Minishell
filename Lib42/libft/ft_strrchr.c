/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lpraca-l <lpraca-l@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 21:15:10 by lpraca-l      #+#    #+#                 */
/*   Updated: 2022/10/22 14:32:00 by lpraca-l      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*The strchr() function locates the first occurrence of c (converted to a
     char) in the string pointed to by s.  The terminating null character is
     considered to be part of the string; therefore if c is `\0', the func-
     tions locate the terminating `\0'.

     The strrchr() function is identical to strchr(), except it locates the
     last occurrence of c.
	  The functions strchr() and strrchr() return a pointer to the located
     character, or NULL if the character does not appear in the string.*/

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*alias;
	int		len;
	char	compare_char;

	compare_char = c;
	alias = (char *) s;
	len = ft_strlen(s);
	while (len != (-1))
	{
		if (alias[len] == compare_char)
			return (alias + len);
		else
			len --;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lpraca-l <lpraca-l@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 20:25:55 by lpraca-l      #+#    #+#                 */
/*   Updated: 2022/10/22 14:30:53 by lpraca-l      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*The strchr() function locates the first occurrence of c (converted to a
     char) in the string pointed to by s.  The terminating null character is
     considered to be part of the string; therefore if c is `\0', the func-
     tions locate the terminating `\0'.
	 The functions strchr() and strrchr() return a pointer to the located
     character, or NULL if the character does not appear in the string.*/

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		count;
	int		len;
	char	*alias;
	char	compare_char;

	compare_char = c;
	count = 0;
	alias = (char *) s;
	len = ft_strlen(s);
	while (count < (len + 1))
	{
		if (alias[count] != compare_char)
			count++;
		else if (alias[count] == compare_char)
			return (alias + count);
	}
	return (0);
}

int	ft_strchr_position(const char *s, int c)
{
	int		count;
	int		len;
	char	*alias;
	char	compare_char;

	compare_char = c;
	count = 0;
	alias = (char *) s;
	len = ft_strlen(s);
	while (count < (len + 1))
	{
		if (alias[count] != compare_char)
			count++;
		else if (alias[count] == compare_char)
			return (count);
	}
	return (-1);
}
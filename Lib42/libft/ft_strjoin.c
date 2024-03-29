/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lpraca-l <lpraca-l@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 14:32:37 by lpraca-l      #+#    #+#                 */
/*   Updated: 2023/08/16 16:25:07 by lpraca-l      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*Allocates (with malloc(3)) and returns a new
string, which is the result of the concatenation
of ’s1’ and ’s2’.
Returns the new string or NULL if the allocation fails.*/

#include "libft.h"
#include <stdio.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	counts1;
	char	*join;
	size_t	len;
	size_t	counts2;

	counts1 = 0;
	counts2 = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	join = ft_calloc_exit((len + 1), sizeof(char));
	while (s1[counts1] != '\0')
	{
		join[counts1] = s1[counts1];
		counts1++;
	}
	while (s2[counts2] != '\0')
	{
		join[counts1] = s2[counts2];
		counts1++;
		counts2++;
	}
	return (join);
}

char	*ft_strjoin_space(char const *s1, char const *s2)
{
	size_t	counts1;
	char	*join;
	size_t	len;
	size_t	counts2;

	counts1 = 0;
	counts2 = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	if (ft_strlen(s1) == 0 || ft_strlen(s2) == 0)
		join = ft_calloc_exit((len + 1), sizeof(char));
	else
		join = ft_calloc_exit((len + 2), sizeof(char));
	while (s1[counts1] != '\0')
	{
		join[counts1] = s1[counts1];
		counts1++;
	}
	if (ft_strlen(s1) != 0)
		join[counts1++] = ' ';
	while (s2[counts2] != '\0')
		join[counts1++] = s2[counts2++];
	return (join);
}

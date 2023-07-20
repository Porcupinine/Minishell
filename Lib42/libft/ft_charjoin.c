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

#include "libft.h"

char	*append_char(char const *s1, char const c)
{
    size_t	counts1;
    char	*join;
    size_t	len;

    counts1 = 0;
    len = ft_strlen(s1) + 1;
    join = malloc((len + 1) * sizeof(char));
    if (join == NULL)
        return (NULL);
    while (s1[counts1] != '\0')
    {
        join[counts1] = s1[counts1];
        counts1++;
    }
    join[counts1] = c;
    counts1++;
    join[counts1] = '\0';
    return (join);
}
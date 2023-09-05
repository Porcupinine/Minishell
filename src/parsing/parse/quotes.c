/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmaessen <dmaessen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 14:13:48 by laura         #+#    #+#                 */
/*   Updated: 2023/09/06 00:20:19 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../Lib42/include/libft.h"

static char	*remove(char *str, char c)
{
	char	*new_str;
	int		count;
	int		count_str;

	count = 0;
	count_str = 0;
	new_str = ft_calloc_exit((ft_strlen(str) - 1), sizeof (char));
	while (str[count_str] != '\0' && str[count_str] != c)
		new_str[count++] = str[count_str++];
	count_str++;
	while (str[count_str] != '\0')
		new_str[count++] = str[count_str++];
	count = (int)ft_strlen(str) - 2;
	count_str = (int)ft_strlen(str);
	while (count_str > 0 && str[count_str] != c)
		new_str[count--] = str[count_str--];
	count_str--;
	new_str[count--] = str[count_str--];
	return (new_str);
}

char	*remove_quotes(char *str)
{
	char	*tmp;

	tmp = str;
	if (ft_strchr(str, '\'') != 0 && ft_strchr(str, '"') != 0)
	{
		if (ft_strchr_position(str, '\'') < ft_strchr_position(str, '"'))
			tmp = remove(str, '\'');
		else
			tmp = remove(str, '"');
	}
	else if (ft_strchr(str, '\'') != 0)
		tmp = remove(str, '\'');
	else if (ft_strchr(str, '"') != 0)
		tmp = remove(str, '"');
	if (tmp != str)
	{
		free(str);
	}
	return (tmp);
}

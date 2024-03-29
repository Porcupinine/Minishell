/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:13:48 by laura             #+#    #+#             */
/*   Updated: 2023/09/07 17:27:21 by dmaessen         ###   ########.fr       */
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
	if (ft_strlen(str) == 2)
		return (ft_strdup(""));
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

static void	whyyyyy(char **str, int *count_new, int *count_og, char c)
{
	while ((*str)[(*count_og)] != c)
		(*str)[(*count_new)++] = (*str)[(*count_og)++];
}

void	remove_quotes2point0(char **str)
{
	int	count_new;
	int	count_og;

	count_og = 0;
	count_new = 0;
	while ((*str)[count_og] != '\0')
	{
		if ((*str)[count_og] == '"')
		{
			count_og++;
			whyyyyy(str, &count_new, &count_og, '"');
			count_og++;
		}
		else if ((*str)[count_og] == '\'')
		{
			count_og++;
			whyyyyy(str, &count_new, &count_og, '\'');
			count_og++;
		}
		else if ((*str)[count_og] != '\0')
			(*str)[count_new++] = (*str)[count_og++];
	}
	(*str)[count_new] = '\0';
}

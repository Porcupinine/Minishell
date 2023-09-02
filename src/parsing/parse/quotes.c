/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:13:48 by laura             #+#    #+#             */
/*   Updated: 2023/09/01 12:10:56 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Lib42/include/libft.h"

char	*remove_quotes(char *str)
{
	char	*tmp;
	int		count_quotes;
	int		count;
	int		count_tmp;

	tmp = NULL;
	count_tmp = 0;
	count = 0;
	if (ft_strchr(str, '\'') != 0 && ft_strchr(str, '"') != 0)
	{
		if (ft_strchr_position(str, '\'') < ft_strchr_position(str, '"'))
			tmp = ft_strtrim(str, "\'");
		else
			tmp = ft_strtrim(str, "\"");
	}
	else if (ft_strchr(str, '\'') != 0)
		tmp = ft_strtrim(str, "\'");
	else
		tmp = ft_strtrim(str, "\"");

//	count_quotes = 0;
//	while (str[count] != '\0')
//	{
//		if (str[count] == '\'' || str[count] == '"')
//			count_quotes++;
//		count++;
//	}
//	count = -1;
//	tmp = ft_calloc_exit(((ft_strlen(str) - count_quotes) + 1), sizeof (char));
//	while (str[++count] != '\0')
//	{
//		if (str[count] != '\'' && str[count] != '"')
//		{
//			tmp[count_tmp] = str[count];
//			count_tmp++;
//		}
//		// count++;
//	}
	return (tmp);
}

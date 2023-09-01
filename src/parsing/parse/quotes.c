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

	count_tmp = 0;
	count = 0;
	count_quotes = 0;
	while (str[count++] != '\0')
	{
		if (str[count] == '\'' || str[count] == '"')
			count_quotes++;
		count++;
	}
	count = 0;
	tmp = ft_calloc_exit(((ft_strlen(str) - count_quotes) + 1), sizeof (char));
	while (str[count++] != '\0')
	{
		if (str[count] != '\'' && str[count] != '"')
		{
			tmp[count_tmp] = str[count];
			count_tmp++;
		}
	}
	return (tmp);
}

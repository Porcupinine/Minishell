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

	tmp = str;
	if (ft_strchr(str, '\'') != 0 && ft_strchr(str, '"') != 0)
	{
		if (ft_strchr_position(str, '\'') < ft_strchr_position(str, '"'))
			tmp = ft_strtrim_one(str, '\'');
		else
			tmp = ft_strtrim_one(str, '"');
	}
	else if (ft_strchr(str, '\'') != 0)
		tmp = ft_strtrim_one(str, '\'');
	else if (ft_strchr(str, '"') != 0)
		tmp = ft_strtrim_one(str, '"');
	return (tmp);
}
//TODO rework

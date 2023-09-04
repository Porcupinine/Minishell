/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarsign2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:22:13 by dmaessen          #+#    #+#             */
/*   Updated: 2023/09/01 13:48:18 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"

int	var_len(char *line, int start)
{
	int	i;

	i = 0;
	if (line[start] == '?')
		return (start + 1);
	while (ft_isalnum(line[start + i]) || line[start + i] == '_')
	{
		if (line[start + i] == ' ')
			break ;
		i++;
	}
	return (start + i);
}

char	*var_name(char *line, int start, int end)
{
	char	*sub;
	char	*name;

	sub = ft_substr(line, start, end);
	name = ft_strjoin(sub, "=");
	free(sub);
	return (name);
}

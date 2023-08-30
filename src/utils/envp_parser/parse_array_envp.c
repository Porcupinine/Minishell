/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_array_envp.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/11 08:03:05 by laura         #+#    #+#                 */
/*   Updated: 2023/08/16 14:37:43 by lpraca-l      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Lib42/include/libft.h"
#include <stdio.h>

void	print_envp(char **mini_envp)
{
	int	count;

	count = 0;
	while (mini_envp[count] != NULL)
	{
		printf("%s\n", mini_envp[count]);
		count++;
	}
}

static int	count_envp(char **envp)
{
	int	count;

	count = 0;
	while (envp[count] != NULL)
	{
		count++;
	}
	return (count);
}

void	parse_array_envp(t_data *mini_data, char **envp)
{
	int		count;

	count = 0;
	mini_data->mini_envp = ft_calloc_exit(count_envp(envp) + 1,
										  sizeof (char *));
	while (envp[count] != NULL)
	{
		mini_data->mini_envp[count] = ft_strdup(envp[count]);
		count++;
	}
	mini_data->mini_envp[count] = NULL;
//	print_envp(mini_data->mini_envp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_free_array.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 14:08:46 by laura         #+#    #+#                 */
/*   Updated: 2023/08/31 14:09:16 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	free_envp_array(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		free(envp[i]);
		i++;
	}
	free(envp);
	envp = NULL;
}

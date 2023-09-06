/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_export3.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/05 23:21:57 by laura         #+#    #+#                 */
/*   Updated: 2023/09/05 23:27:10 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/exec.h"
#include "../../Lib42/include/libft.h"
#include "../../include/utils.h"

int	replace_envp_var(t_data *mini, char *name, char *res)
{
	int	i;

	i = 0;
	while (mini->mini_envp[i])
	{
		if (ft_strncmp(mini->mini_envp[i], name,
				ft_strlen(name) - 1) == 0)
		{
			free(mini->mini_envp[i]);
			mini->mini_envp[i] = ft_strjoin(name, res);
			free(res);
			return (free(name), set_exit_code(mini, 0), 0);
		}
		i++;
	}
	return (1);
}

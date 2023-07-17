/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_arg_node.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 17:31:19 by laura         #+#    #+#                 */
/*   Updated: 2023/07/17 17:31:34 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdlib.h>
#include "../../Lib42/include/libft.h"

void	add_arg(t_env_args *args, char *name, char *value)
{
	t_env_args	*new_arg;

	new_arg = malloc(sizeof(t_env_args));
	if (new_arg == NULL)
		ft_error("Malloc arg fail\n");
	args->next = new_arg;
	new_arg->name = name;
	new_arg->content = value;
	new_arg->next = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_list_envp.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmaessen <dmaessen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/11 08:03:49 by laura         #+#    #+#                 */
/*   Updated: 2023/08/31 14:10:42 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../Lib42/include/libft.h"
#include <stdio.h>

static t_mini_envp_list	*find_last_envp(t_mini_envp_list *mini_envp_list)
{
	if (mini_envp_list == NULL)
		return (NULL);
	while (mini_envp_list->next != NULL)
		mini_envp_list = mini_envp_list->next;
	return (mini_envp_list);
}

static void	add_envp_node(t_mini_envp_list **envp_list, char *str)
{
	t_mini_envp_list	*new_envp;
	t_mini_envp_list	*last_node;

	last_node = NULL;
	new_envp = ft_calloc_exit(1, sizeof(t_mini_envp_list));
	new_envp->str = str;
	new_envp->next = NULL;
	if (*envp_list == NULL)
		*envp_list = new_envp;
	else
	{
		last_node = find_last_envp(*envp_list);
		last_node->next = new_envp;
	}
}

void	parse_list_envp(t_data *mini_data, char **envp)
{
	int	count;

	count = 0;
	while (envp[count] != NULL)
	{
		add_envp_node(&mini_data->mini_envp_list, envp[count]);
		count++;
	}
}

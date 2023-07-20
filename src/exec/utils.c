/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domi <domi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:19:38 by dmaessen          #+#    #+#             */
/*   Updated: 2023/07/20 16:47:14 by domi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env_var.h"
#include "../../include/pipes.h"
#include "../../Lib42/include/libft.h"

int	lst_size(t_commands *lst)
{
	int			count;
	t_commands	*position;

	count = 0;
	position = lst;
	while (position != NULL)
	{
		position = position->next;
		count++;
	}
	return (count);
}

t_pid	*pid_lstnew(void *content)
{
	t_pid	*new_item;

	new_item = malloc(1 * sizeof(t_pid));
	if (new_item == NULL)
		return (NULL);
	new_item->content = content;
	new_item->next = NULL;
	return (new_item);
}

void	pid_lstadd_back(t_pid **lst, t_pid *new_node)
{
	t_pid	*last_node;

	if (new_node == NULL)
		return ;
	else if (*lst == NULL)
		*lst = new_node;
	else
	{
		last_node = pid_lstlast(*lst);
		last_node->next = new_node;
	}
}

t_pid	*pid_lstlast(t_pid *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

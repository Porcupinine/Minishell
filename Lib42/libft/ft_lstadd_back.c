/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_back.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lpraca-l <lplacerdadesign@gmail.com>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/23 18:19:48 by lpraca-l      #+#    #+#                 */
/*   Updated: 2022/10/23 20:49:29 by lpraca-l      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*Adds the node ’new’ at the end of the list.*/

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_node)
{
	t_list	*last_node;

	if (new_node == NULL)
		return ;
	else if (*lst == NULL)
		*lst = new_node;
	else
	{
		last_node = ft_lstlast(*lst);
		last_node->next = new_node;
	}
}

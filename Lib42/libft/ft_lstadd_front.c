/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_front.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lpraca-l <lplacerdadesign@gmail.com>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/23 17:01:10 by lpraca-l      #+#    #+#                 */
/*   Updated: 2022/10/23 17:46:03 by lpraca-l      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*Adds the node ’new’ at the beginning of the list.*/

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new_node)
{
	if (lst == NULL || new_node == NULL)
		return ;
	new_node->next = *lst;
	*lst = new_node;
}

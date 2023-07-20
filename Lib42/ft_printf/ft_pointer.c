/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_pointer.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/20 23:16:09 by laura         #+#    #+#                 */
/*   Updated: 2023/01/23 18:25:31 by lpraca-l      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @brief prints a pointer
 * 
 * @param ptr pointer to be printed
 * @return int count = howe many char have been printed
 */
int	ft_pointer( unsigned long ptr)
{
	int	count;

	count = 0;
	count = ft_string("0x");
	if (count == -1)
		return (-1);
	count += ft_putnbr_ulong(ptr, "0123456789abcdef");
	return (count);
}

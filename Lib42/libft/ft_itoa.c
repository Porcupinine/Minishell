/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domi <domi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 13:45:57 by lpraca-l          #+#    #+#             */
/*   Updated: 2023/10/25 10:22:52 by domi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Allocates (with malloc(3)) and returns a string
representing the integer received as an argument.
Negative numbers must be handled.
returns The string representing the integer NULL if the allocation fails.
*/

#include "libft.h"

static size_t	n_size(int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count++;
	}
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static int	n_absolut(int n)
{
	if (n < 0)
		n *= (-1);
	return (n);
}

void	write_nb(char *nb_char, long long nb, size_t nb_size)
{
	while (nb != 0)
	{
		nb_char[nb_size - 1] = (48 + n_absolut(nb % 10));
		nb = nb / 10;
		nb_size--;
	}
}

char	*ft_itoa(int n)
{
	long long	nb;
	size_t		nb_size;
	char		*nb_char;

	nb = n;
	nb_size = n_size(nb);
	if (nb == 0)
		nb_size = 1;
	nb_char = ft_calloc_exit((nb_size + 1), sizeof(char));
	ft_memset(nb_char, 'a', nb_size);
	nb_char[nb_size + 1] = '\0';
	if (nb < 0)
	{
		nb_char[0] = '-';
	}
	if (n == 0)
		nb_char[0] = '0';
	write_nb(nb_char, nb, nb_size);
	return (nb_char);
}

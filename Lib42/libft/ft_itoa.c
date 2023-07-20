/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lpraca-l <lplacerdadesign@gmail.com>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/22 13:45:57 by lpraca-l      #+#    #+#                 */
/*   Updated: 2022/10/26 17:59:08 by lpraca-l      ########   odam.nl         */
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
	nb_char = ft_calloc((nb_size + 1), sizeof(char));
	if (nb_char == NULL)
		return (NULL);
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

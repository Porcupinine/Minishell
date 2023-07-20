/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lpraca-l <lpraca-l@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 17:22:11 by lpraca-l      #+#    #+#                 */
/*   Updated: 2022/10/31 18:14:05 by lpraca-l      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*Outputs the integer ’n’ to the given file
descriptor.
 n: The integer to output.
fd: The file descriptor on which to write.*/

#include "libft.h"

long int	exponential(long x, long n)
{
	long int	i;
	long int	number;

	number = 1;
	i = 0;
	while (i < n)
	{
		number *= x;
		i++;
	}
	return (number);
}

void	ft_putnbr_fd(int toconvert, int fd)
{
	long int	digit;
	long int	n;
	long int	exp;
	long int	original;
	long int	nb_long;

	nb_long = toconvert;
	if (nb_long < 0)
	{
		ft_putchar_fd('-', fd);
		nb_long = nb_long * (-1);
	}
	original = nb_long;
	n = 10;
	while (n >= 1)
	{
		exp = exponential(10, n);
		digit = (nb_long / exp);
		if (original > exp)
			ft_putchar_fd((digit + 48), fd);
		nb_long = nb_long - (digit * exp);
		n--;
	}
	ft_putchar_fd((nb_long + 48), fd);
}

// void	ft_putnbr_fd(int n, int fd)
// {
// 	char	*number;

// 	number = ft_itoa(n);
// 	if (number == NULL)
// 		return ;
// 	ft_putstr_fd(number, fd);
// 	free(number);
// }

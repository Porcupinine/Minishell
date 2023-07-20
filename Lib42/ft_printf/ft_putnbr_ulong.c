/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_ulong.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 08:36:00 by laura         #+#    #+#                 */
/*   Updated: 2023/01/23 19:39:26 by lpraca-l      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

/**
 * @brief print number
 * 
 * @param conv number as string
 * @param count_conv amount to print
 * @return int amount of printed chars
 */
static int	print_re(char *conv, int count_conv)
{
	int		count;

	count = count_conv -1;
	while (count >= 0)
		if (write(1, &(conv[count--]), 1) == -1)
			return (-1);
	return (count_conv);
}

/**
 * @brief checks the base to be used
 * 
 * @param base base input
 * @return int 0 if base is invalid or 1 if base is valid
 */
static int	check_base(char *base)
{
	int	count;
	int	mv_count;
	int	base_size;

	base_size = 0;
	count = 0;
	while (base[base_size] != '\0')
		base_size++;
	if (base_size < 2)
		return (0);
	while (base[count] != '\0')
	{
		if (base[count] == '-' || base[count] == '+')
			return (0);
		mv_count = count + 1;
		while (base[mv_count] != '\0')
		{
			if (base[count] == base[mv_count++])
				return (0);
		}
		count++;
	}
	return (1);
}

/**
 * @brief convert nbr to string
 * 
 * @param nbr number
 * @param base base to be used
 * @return int amount of printed chars
 */
int	ft_putnbr_ulong(unsigned long long nbr, char*base)
{
	unsigned long long	base_size;
	char				conv[64];
	int					count_conv;
	unsigned long long	leftover;

	count_conv = 0;
	base_size = 0;
	if (check_base(base) == 0)
		return (0);
	while (base[base_size] != '\0')
		base_size++;
	while (nbr >= base_size)
	{
		leftover = nbr % base_size;
		nbr = nbr / base_size;
		conv[count_conv++] = base[leftover];
	}
	conv[count_conv++] = base[nbr];
	count_conv = print_re(conv, count_conv);
	return (count_conv);
}

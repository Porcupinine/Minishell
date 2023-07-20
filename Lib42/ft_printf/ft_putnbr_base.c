/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_base.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 08:36:00 by laura         #+#    #+#                 */
/*   Updated: 2023/01/23 19:38:15 by lpraca-l      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/**
 * @brief prints the result 
 * 
 * @param conv number as a string
 * @param count_conv amount of chars
 * @param original original number to test in case its negative
 * @return int amount of printed chars
 */
static int	print_result(char *conv, int count_conv, long long original)
{
	char	c;
	int		count;

	count = count_conv -1;
	c = '-';
	if (original < 0)
	{
		count_conv++;
		if (write(1, &c, 1) == -1)
			return (-1);
	}
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
int	ft_putnbr_base(long long nbr, char*base)
{
	int			base_size;
	char		conv[64];
	int			count_conv;
	long long	leftover;
	long long	nbr_module;

	nbr_module = nbr;
	count_conv = 0;
	base_size = 0;
	if (check_base(base) == 0)
		return (0);
	if (nbr_module < 0)
		nbr_module *= (-1);
	while (base[base_size] != '\0')
		base_size++;
	while (nbr_module >= base_size)
	{
		leftover = nbr_module % base_size;
		nbr_module = nbr_module / base_size;
		conv[count_conv++] = base[leftover];
	}
	conv[count_conv++] = base[nbr_module];
	count_conv = print_result(conv, count_conv, nbr);
	return (count_conv);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_char_string.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/19 16:23:18 by laura         #+#    #+#                 */
/*   Updated: 2023/01/23 18:27:51 by lpraca-l      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

/**
 * @brief prints a unic char
 * 
 * @param c char to be printed
 * @return int amount of printed char aka 1 or -1 in case write fails
 */
int	ft_char(int c)
{
	if (write(1, &c, 1) == -1)
		return (-1);
	return (1);
}

/**
 * @brief prints given string or null in case of empty string
 * 
 * @param str string to be printed
 * @return int amount of printed char aka 1 or -1 in case write fails
 */
int	ft_string(char *str)
{
	int	char_count;

	char_count = 0;
	if (str == NULL)
	{
		if (write (1, "(null)", 6) == -1)
			return (-1);
		return (6);
	}
	while (str[char_count] != '\0')
	{
		if (ft_char(str[char_count]) == -1)
			return (-1);
		char_count++;
	}
	return (char_count);
}

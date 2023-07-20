/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/19 14:34:18 by laura         #+#    #+#                 */
/*   Updated: 2023/01/23 18:24:56 by lpraca-l      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*%c Prints a single character.
• %s Prints a string (as defined by the common C convention).
• %p The void * pointer argument has to be printed in hexadecimal format.
• %d Prints a decimal (base 10) number.
• %i Prints an integer in base 10.
• %u Prints an unsigned decimal (base 10) number.
• %x Prints a number in hexadecimal (base 16) lowercase format.
• %X Prints a number in hexadecimal (base 16) uppercase format.
• %% Prints a percent sign.
 *
 * Don’t implement the buffer management of the original printf().
• Your function has to handle the following conversions: cspdiuxX%
• Your function will be compared against the original printf().
• You must use the command ar to create your library.
Using the libtool command is forbidden.
• Your libftprintf.a has to be created at the root of your repository.

 ERROR return -1 else return number of char
 */

#include <stdarg.h>
#include "ft_printf.h"
#include "libft.h"

/**
 * @brief checks flag to be printed and decide how to proceed
 * 
 * @param content content of the list
 * @param type flag to be printed
 * @return int i = how many characters were printed
 */
static int	ft_type(va_list content, char type)
{
	int	i;

	i = 0;
	if (type == '%')
		i += ft_char(type);
	else if (type == 'c')
		i += ft_char(va_arg(content, int));
	else if (type == 's')
		i += ft_string(va_arg(content, char *));
	else if (type == 'p')
		i += ft_pointer(va_arg(content, unsigned long long));
	else if (type == 'd' || type == 'i')
		i += ft_putnbr_base(va_arg(content, int), "0123456789");
	else if (type == 'u')
		i += ft_putnbr_base(va_arg(content, unsigned int), "0123456789");
	else if (type == 'x')
		i += ft_putnbr_ulong(va_arg(content, unsigned int), "0123456789abcdef");
	else if (type == 'X')
		i += ft_putnbr_ulong(va_arg(content, unsigned int), "0123456789ABCDEF");
	else
		return (0);
	return (i);
}

/**
 * @brief looks for % followed by flags, in case a percentage is not followed 
 * by a valid flag, skips the percentage sing and keep going on. If no pecentage
 * is found, just print the current char.
 * 
 * @param str string to be printed
 * @param content list were content is stored
 * @param ret amount of chars read on type function
 * @return int char_count = how many chars have been printed 
 */
static int	real_printf(const char *str, va_list content, int ret, int c_count)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '%' && !ft_strchr("cspdiuxX%", str[i + 1]))
			i++;
		else if (str[i] == '%' && ft_strchr("cspdiuxX%", str[i + 1]))
		{
			ret = ft_type(content, str[i + 1]);
			if (ret == (-1))
				return (-1);
			c_count += ret;
			i += 2;
		}
		else
		{
			ret = ft_char(str[i]);
			if (ret == (-1))
				return (-1);
			i++;
			c_count++;
		}
	}
	return (c_count);
}

int	ft_printf(const char *str, ...)
{
	int		char_counter;
	va_list	content;

	char_counter = 0;
	va_start(content, str);
	char_counter = real_printf(str, content, 0, char_counter);
	va_end(content);
	return (char_counter);
}

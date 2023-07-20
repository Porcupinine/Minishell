/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putchar_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lpraca-l <lpraca-l@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 16:56:32 by lpraca-l      #+#    #+#                 */
/*   Updated: 2022/10/17 17:00:29 by lpraca-l      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*Outputs the character ’c’ to the given file
descriptor.
c: The character to output.
fd: The file descriptor on which to write.*/

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

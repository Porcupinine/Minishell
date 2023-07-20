/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/19 14:34:24 by laura         #+#    #+#                 */
/*   Updated: 2023/01/23 18:13:57 by lpraca-l      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stddef.h>

int		ft_char(int c);
int		ft_string(char *str);
int		ft_pointer(unsigned long ptr);
size_t	ft_strlen(const char *c);
char	*ft_strchr(const char *s, int c);
int		ft_putnbr_base(long long nbr, char*base);
int		ft_putnbr_ulong(unsigned long long nbr, char*base);
int		ft_printf(const char *str, ...);

#endif
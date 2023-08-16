/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lpraca-l <lplacerdadesign@gmail.com>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/16 20:58:58 by lpraca-l      #+#    #+#                 */
/*   Updated: 2023/08/16 16:26:17 by lpraca-l      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*The atoi() function converts the initial portion of the string pointed to
 by nptr to int.  The behavior is the same as strtol(nptr, NULL, 10);
except that atoi() does not detect errors.
The atol() and atoll() functions behave the same as atoi(), except that 
they convert the  initial  portion  of the string to their return type of
long or long long.
return The converted value.*/

#include "libft.h"

static int	deal_isspace_issign(char *a, int *count, int *count_m, int *count_p)
{
	while (a[*count] == ' ' || a[*count] == '\t'
		|| a[*count] == '\r' || a[*count] == '\n'
		|| a[*count] == '\v' || a[*count] == '\f')
		(*count)++;
	while (a[*count] == '-')
	{
		if (a[*count + 1] == '+' || a[*count + 1] == '-')
			return (0);
		(*count)++;
		(*count_m)++;
	}
	if (a[*count] == '+')
	{
		if (a[*count + 1] == '+')
			return (0);
		(*count)++;
		(*count_p)++;
	}
	return (1);
}

int	ft_atoi(const char *nptr)
{
	int		count;
	char	*alias;
	int		nbr;
	int		count_m;
	int		count_p;

	alias = (char *) nptr;
	count = 0;
	count_m = 0;
	nbr = 0;
	count_p = 0;
	if (deal_isspace_issign(alias, &count, &count_m, &count_p) == 0)
		return (0);
	while (ft_isdigit(alias[count]) != 0)
	{
		nbr = ((nbr * 10) + (alias[count] - 48));
		count++;
	}
	if (count_m == 1)
	{
		nbr = (-1 * nbr);
		return (nbr);
	}
	return (nbr);
}

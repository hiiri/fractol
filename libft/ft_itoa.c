/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 16:31:16 by alcohen           #+#    #+#             */
/*   Updated: 2019/11/03 00:22:28 by alcohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	num_len(int n)
{
	int	neg;

	neg = (n < 0) ? 1 : 0;
	if (n < 0)
		n *= -1;
	if (n >= 1000000000)
		return (10 + neg);
	if (n >= 100000000)
		return (9 + neg);
	if (n >= 10000000)
		return (8 + neg);
	if (n >= 1000000)
		return (7 + neg);
	if (n >= 100000)
		return (6 + neg);
	if (n >= 10000)
		return (5 + neg);
	if (n >= 1000)
		return (4 + neg);
	if (n >= 100)
		return (3 + neg);
	if (n >= 10)
		return (2 + neg);
	return (1 + neg);
}

static char	*edge_cases(int n)
{
	if (n == 0)
	{
		return (ft_strdup("0"));
	}
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	return (NULL);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		sign;

	len = num_len(n);
	if (!(str = (char *)malloc(len + 1)))
		return (NULL);
	if (edge_cases(n))
		return (edge_cases(n));
	sign = 1;
	if (n < 0)
		sign = -1;
	n *= sign;
	str[len--] = '\0';
	if (sign == -1)
		str[0] = '-';
	while (len >= 0 && str[len] != '-')
	{
		str[len--] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 20:17:46 by alcohen           #+#    #+#             */
/*   Updated: 2020/02/28 15:45:00 by alcohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	len_i;
	char	*sub;

	if (!(sub = (char *)malloc(len * sizeof(char) + 1)))
	{
		return (NULL);
	}
	i = 0;
	len_i = 0;
	while (s[i] && len != len_i)
	{
		while (i == start && len_i < len)
		{
			sub[len_i] = s[i + len_i];
			len_i++;
		}
		i++;
	}
	sub[len_i] = '\0';
	return (sub);
}

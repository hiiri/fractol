/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 18:39:06 by alcohen           #+#    #+#             */
/*   Updated: 2019/10/31 23:44:28 by alcohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strrev(char *str)
{
	size_t	i;
	size_t	len;
	char	*rev;
	size_t	j;

	len = ft_strlen(str);
	i = 0;
	j = len - 1;
	if (!(rev = (char *)malloc(len * sizeof(str) + 1)))
		return (NULL);
	while (str && i < len)
	{
		rev[i] = str[j];
		i++;
		j--;
	}
	rev[i] = '\0';
	return (rev);
}

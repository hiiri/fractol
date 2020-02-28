/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 20:35:04 by alcohen           #+#    #+#             */
/*   Updated: 2020/02/28 15:47:28 by alcohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		len;
	char	*join;

	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(join = (char *)malloc(len * sizeof(char) + 1)))
	{
		return (NULL);
	}
	i = 0;
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	j = i;
	i = 0;
	while (s2[i])
	{
		join[j + i] = s2[i];
		i++;
	}
	join[j + i] = '\0';
	return (join);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 21:50:58 by alcohen           #+#    #+#             */
/*   Updated: 2019/10/25 22:04:45 by alcohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void	*mem;
	size_t	i;

	if (!(mem = (void *)malloc(size)))
	{
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		((char *)mem)[i] = 0;
		i++;
	}
	return (mem);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 21:04:21 by alcohen           #+#    #+#             */
/*   Updated: 2019/10/25 21:48:36 by alcohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	start;
	size_t	len;
	size_t	end;

	start = 0;
	while (s[start] && ft_iswhitespace(s[start]))
	{
		start++;
	}
	end = ft_strlen(s) - 1;
	if (start == end + 1)
		return ("");
	while (end >= 0 && ft_iswhitespace(s[end]))
	{
		end--;
	}
	len = end - start + 1;
	return (ft_strsub(s, (unsigned int)start, len));
}

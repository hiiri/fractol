/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 20:53:06 by alcohen           #+#    #+#             */
/*   Updated: 2019/11/02 23:27:52 by alcohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	ft_count_words(char const *s, char c)
{
	size_t	i;
	size_t	count;
	size_t	j;
	int		flag;

	i = 0;
	count = 0;
	j = 0;
	flag = 0;
	while (s[i])
	{
		if (flag && s[i] == c)
			flag = 0;
		if (!flag && s[i] != c)
		{
			flag = 1;
			count++;
		}
		i++;
	}
	return (count);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t	word_count;
	char	**arr;
	size_t	arr_i;
	size_t	i;
	size_t	start;

	word_count = ft_count_words(s, c);
	if (!(arr = (char **)malloc(sizeof(char *) * word_count + 1)))
		return (NULL);
	i = 0;
	arr_i = 0;
	while (arr_i < word_count)
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		arr[arr_i] = ft_strsub(s, (unsigned int)start, i - start);
		i++;
		arr_i++;
	}
	arr[arr_i] = NULL;
	i = 0;
	return (arr);
}

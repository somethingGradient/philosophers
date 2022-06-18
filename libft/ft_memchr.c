/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 22:08:17 by akitty            #+#    #+#             */
/*   Updated: 2021/10/05 22:08:19 by akitty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void *arr, int c, size_t n)
{
	size_t			i;
	unsigned char	*src_temp;

	i = 0;
	src_temp = (unsigned char *)arr;
	while (i < n)
	{
		if (src_temp[i] == (unsigned char)c)
			return ((void *)&src_temp[i]);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 10:12:32 by akitty            #+#    #+#             */
/*   Updated: 2021/10/11 10:12:36 by akitty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*arr;
	size_t	bytes;

	bytes = n * size;
	arr = malloc(bytes);
	if (arr)
		ft_memset(arr, 0, bytes);
	return (arr);
}

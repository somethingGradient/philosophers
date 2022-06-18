/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 18:00:43 by akitty            #+#    #+#             */
/*   Updated: 2021/10/05 18:06:09 by akitty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*temp;
	char	*temp2;

	if (!dest && !src)
		return (0);
	temp = (char *)src;
	temp2 = (char *)dest;
	i = 0;
	while (i < n)
	{
		temp2[i] = temp[i];
		i++;
	}
	return (temp2);
}

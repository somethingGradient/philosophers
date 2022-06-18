/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 18:19:38 by akitty            #+#    #+#             */
/*   Updated: 2021/10/05 18:19:39 by akitty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, void *src, size_t n)
{
	char			*src_temp;
	char			*dest_temp;
	size_t			i;

	src_temp = (char *)src;
	dest_temp = (char *)dest;
	i = 0;
	if (dest == 0 && src == 0)
		return (0);
	if (dest_temp > src_temp)
	{
		while (n-- > 0)
			dest_temp[n] = src_temp[n];
	}
	else
	{
		while (i < n)
		{
			dest_temp[i] = src_temp[i];
			i++;
		}
	}
	return (dest_temp);
}

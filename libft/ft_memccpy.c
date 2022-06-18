/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 21:33:33 by akitty            #+#    #+#             */
/*   Updated: 2021/10/05 21:33:35 by akitty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, void *src, int c, size_t n)
{
	size_t			i;
	char			*src_temp;
	char			*dest_temp;

	if (dest == 0 && src == 0)
		return (0);
	src_temp = (char *)src;
	dest_temp = (char *)dest;
	i = 0;
	while (i < n && src_temp[i] != (char)c)
	{
		dest_temp[i] = src_temp[i];
		i++;
	}
	if (i == n)
		return (0);
	else
	{
		dest_temp[i] = src_temp[i];
		i++;
		return (&dest_temp[i]);
	}
}

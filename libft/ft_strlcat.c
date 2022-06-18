/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 16:40:01 by akitty            #+#    #+#             */
/*   Updated: 2021/10/06 16:40:02 by akitty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char	*temp_src;
	size_t	i;
	size_t	len_dst;
	size_t	len_src;
	size_t	result;

	temp_src = (char *)src;
	i = 0;
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(temp_src);
	result = len_dst + len_src;
	if (size <= len_dst)
		return (len_src + size);
	while (*dst)
		dst++;
	while ((i < size - (result - len_src) - 1) && temp_src[i])
	{
		dst[i] = temp_src[i];
		i++;
	}
	dst[i] = '\0';
	return (result);
}

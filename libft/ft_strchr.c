/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:41:18 by akitty            #+#    #+#             */
/*   Updated: 2021/10/06 15:41:20 by akitty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*temp_s;

	i = 0;
	temp_s = (char *)s;
	while (temp_s[i])
	{
		if (temp_s[i] == (char)c)
			return (&temp_s[i]);
		i++;
	}
	if (temp_s[i] == '\0' && c == '\0')
		return (&temp_s[i]);
	return (0);
}

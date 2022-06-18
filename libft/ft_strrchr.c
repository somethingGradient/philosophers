/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:49:34 by akitty            #+#    #+#             */
/*   Updated: 2021/10/06 15:49:35 by akitty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*temp_s;

	temp_s = (char *)s;
	i = ft_strlen(temp_s);
	if (temp_s[i] == '\0' && c == '\0')
		return (&temp_s[i]);
	while (i >= 0)
	{
		if (temp_s[i] == (char)c)
			return (&temp_s[i]);
		i--;
	}
	return (0);
}

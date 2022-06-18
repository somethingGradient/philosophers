/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                          :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: akitty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:14:10 by akitty            #+#    #+#             */
/*   Updated: 2021/10/17 12:14:11 by akitty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	malloc_error(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free (arr);
}

static size_t	get_count_words(char *str, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (ft_strlen(str) == 0)
		return (0);
	while (str[i] && str[i] == c)
		i++;
	while (str[i])
	{
		if (str[i] == c)
		{
			count++;
			while (str[i] && str[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (str[i - 1] != c)
		count++;
	return (count);
}

static char	*get_str(char const *s, char c)
{
	size_t	i;
	char	*str;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (0);
	ft_strlcpy(str, s, i + 1);
	return (str);
}

static int	fill_array(char **array, char *str, char c)
{
	size_t	word_index;

	word_index = 0;
	while (*str && *str == c)
		str++;
	while (*str)
	{
		array[word_index] = get_str((char *)str, c);
		if (!array[word_index])
			return (0);
		++word_index;
		while (*str && *str != c)
			str++;
		if (c != '\0')
		{
			while (*str == c)
				str++;
		}
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	size_t	count_words;
	char	**array;

	if (!s)
		return (0);
	count_words = get_count_words((char *)s, c);
	array = (char **)malloc(sizeof(char *) * (count_words + 1));
	if (!array)
		return (0);
	array[count_words] = 0;
	if (!fill_array(array, (char *)s, c))
	{
		malloc_error(array);
		return (0);
	}
	return (array);
}

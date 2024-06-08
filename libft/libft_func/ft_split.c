/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguandr <miguandr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 18:11:54 by miguandr          #+#    #+#             */
/*   Updated: 2024/03/25 19:58:14 by miguandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*ft_split -- split a string into an array of words*/
static size_t	ft_words(char const *s, char delimiter)
{
	int		i;
	size_t	size;

	i = 0;
	size = 0;
	while (s[i])
	{
		while (s[i] && s[i] == delimiter)
			i++;
		if (s[i])
		{
			while (s[i] && s[i] != delimiter)
				i++;
			size++;
		}
	}
	return (size);
}

static char	**ft_allocation(char **array, char const *s, char c)
{
	int		i;
	size_t	count;
	int		start;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			array[count] = ft_substr(s, start, (i - start));
			count++;
		}
	}
	array[count] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;

	if (!s)
		return (NULL);
	array = (char **)malloc(sizeof(char *) * (ft_words(s, c) + 1));
	if (!array)
		return (NULL);
	ft_allocation(array, s, c);
	return (array);
}

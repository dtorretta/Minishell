/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguandr <miguandr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 19:08:58 by miguandr          #+#    #+#             */
/*   Updated: 2024/03/25 19:58:52 by miguandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*strnstr -- locate a substring in a string*/
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needlen;

	if (*needle == 0)
		return ((char *)haystack);
	if (len == 0)
		return (0);
	needlen = ft_strlen(needle);
	while (*haystack && needlen <= len)
	{
		if (*haystack == *needle && ft_strncmp(haystack, needle, needlen) == 0)
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}

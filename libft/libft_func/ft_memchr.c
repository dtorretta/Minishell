/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguandr <miguandr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:43:03 by miguandr          #+#    #+#             */
/*   Updated: 2024/03/25 19:57:29 by miguandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*memchr -- locate byte in byte string*/
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*string;

	string = (unsigned char *)s;
	c = (unsigned char)c;
	while (n && *string != c)
	{
		string++;
		n--;
	}
	if (n)
		return ((void *)string);
	else
		return (NULL);
}

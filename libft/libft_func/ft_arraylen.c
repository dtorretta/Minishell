/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraylen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguandr <miguandr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:35:00 by miguandr          #+#    #+#             */
/*   Updated: 2024/07/17 18:44:00 by miguandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_arraylen(char **array)
{
	size_t	i;
	size_t	total_len;

	i = 0;
	total_len = 0;
	while (array[i])
	{
		total_len += ft_strlen(array[i]) + 1;
		i++;
	}
	total_len--;
	return (total_len);
}

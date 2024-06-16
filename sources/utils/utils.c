/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguandr <miguandr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:29:08 by miguandr          #+#    #+#             */
/*   Updated: 2024/06/14 19:03:17 by miguandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header_mig.h"

char	**dup_str(char **array)
{
	char	**result;
	size_t	i;

	i = 0;
	if (array == NULL)
		return (NULL);
	while (array[i] != NULL)
		i++;
	result = ft_calloc(sizeof(char *), i + 1);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (array[i])
	{
		result[i] = ft_strdup(array[i]);
		if (result[i] == NULL)
		{
			ft_free_array(result);
			return (NULL); // probar return (result) en caso de fallo!!
		}
		i++;
	}
	return (result);
}

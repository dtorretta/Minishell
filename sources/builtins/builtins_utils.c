/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 01:22:11 by marvin            #+#    #+#             */
/*   Updated: 2024/06/26 01:22:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h" //modifica el nombre

void print_array(char **array, int i)
{
	while (array[i])
	{
		ft_putstr_fd(array[i], STDERR_FILENO);
		i++;
		if(array[i])
			write(2, " ", 1);        
	}
}

char **new_array(char **array, char *str)
{
	char **new_array;
	int i;
	
	i = 0;
	while(array[i])
		i++;
	new_array = ft_calloc((i + 2), sizeof(char*));
	if (!new_array)
		return (NULL); //check
	i = 0;
	
	while(array[i])
	{
		new_array[i] = ft_strdup(array[i]);
		i++;
	}
	new_array[i] = str;
	return(new_array);
}

char *delete_quotes (char *str) //ver si la tiene migue
{
	char	*result;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	result = ft_calloc((len + 1), sizeof(char *));
	while (i < len)
	{
		if (str[i] != '\'' && str[i] != '\"')
			result[j++] = str[i];
		i++;
	}
	return (result);
}
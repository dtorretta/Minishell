/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_variables.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:39:40 by miguandr          #+#    #+#             */
/*   Updated: 2024/07/30 21:34:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header_mig.h"

char	*get_variable_name(const char *str, t_mshell *data)
{
	char	*var_name;
	int		len;

	len = 0;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	var_name = ft_calloc(len + 1, sizeof(char));
	if (!var_name)
		handle_error(data, 0);
	ft_strncpy(var_name, str, len);
	return (var_name);
}

char	*get_variable_value(t_mshell *data, char *var_name)
{
	int	i;
	int	var_len;

	i = 0;
	var_len = ft_strlen(var_name);
	while (data->envp[i] != NULL)
	{
		if (ft_strncmp(data->envp[i], var_name, var_len) == 0
			&& data->envp[i][var_len] == '=')
			return (ft_strdup(data->envp[i] + var_len + 1));
		i++;
	}
	return (NULL);
}

//lo puse en expander_utils

// char	*expand_variable(t_mshell *data, const char *str, int *index)
// {
// 	char	*var_name;
// 	char	*var_value;

// 	if (str[1] == '?')
// 	{
// 		var_value = ft_itoa(data->exit_code);
// 		*index += 2;
// 		return (var_value);
// 	}
// 	else
// 	{
// 		var_name = get_variable_name(str + 1, data);
// 		var_value = get_variable_value(data, var_name);
// 		*index += ft_strlen(var_name) + 1;
// 		free(var_name);
// 		if (var_value)
// 			return (var_value);
// 		else
// 			return (NULL);
// 	}
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:39:40 by miguandr          #+#    #+#             */
/*   Updated: 2024/07/14 17:17:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header_mig.h"

char	*remove_single_quote(char *str)
{
	char	*result;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	result = ft_calloc(len + 1, sizeof(char));
	if (!result)
		return (NULL);
	while (i < len)
	{
		if (str[i] != '\'')
			result[j++] = str[i];
		i++;
	}
	return (result);
}

char	*get_variable_name(const char *str)
{
	char	*var_name;
	int		len;

	len = 0;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	var_name = ft_calloc(len + 1, sizeof(char));
	if (!var_name)
		return (NULL);
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

char	*expand_variable(t_mshell *data, const char *str, int *index)
{
	char	*var_name;
	char	*var_value;

	var_name = get_variable_name(str + 1);
	if (!var_name)
		return (NULL);
	var_value = get_variable_value(data, var_name);
	*index += ft_strlen(var_name) + 1;
	free(var_name);
	if (var_value)
		return (var_value);
	else
		return (NULL);
}

/*delete later*/
/*char	*expand_quoted_variable(t_mshell *data, char *str, int *i, char *result)
{
	char	*var_value;
	int		len;
	int		result_len;

	var_value = NULL;
	len = ft_strlen(str);
	result_len = 0;
	while (*i < len)
	{
		if (str[*i] == '\'')
		{
			(*i)++;
			return (result);
		}
		else if (str[*i] == '$')
		{
			var_value = expand_variable(data, str + *i, i);
			ft_strcpy(result + ft_strlen(result), var_value);
			free (var_value);
		}
		else
			result[ft_strlen(result[result_len])] = str[*i];
		(*i)++;
	}
	return (result);
}*/

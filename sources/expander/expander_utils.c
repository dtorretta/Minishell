/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguandr <miguandr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:39:40 by miguandr          #+#    #+#             */
/*   Updated: 2024/06/30 19:24:03 by miguandr         ###   ########.fr       */
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
	result = (char *)malloc(len + 1);
	while (i < len)
	{
		if (str[i] != '\'')
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

char	*get_variable_name(const char *str)
{
	char	*var_name;
	int		len;

	len = 0;
	var_name = (char *)malloc(len + 1);
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	ft_strncpy(var_name, str, len);
	var_name[len] = '\0';
	return (var_name);
}

char	*get_variable_value(t_mshell *data, char *var_name)
{
	int	i;
	int	var_len;

	i = 0;
	var_len = ft_strlen(var_name);
	if (!var_name)
		return (NULL);
	while (data->envp[i] != NULL)
	{
		if (ft_strncmp(data->envp[i], var_name, var_len) == 0
			&& data->envp[i][var_len] == '=')
			return (data->envp[i] + var_len + 1);
	}
	return (NULL);
}

char	*expand_variable(t_mshell *data, const char *str, int *index)
{
	char	*var_name;
	char	*var_value;

	var_name = get_variable_name(str + 1);
	var_value = get_variable_value(data, var_name);
	*index += ft_strlen(var_name);
	free(var_name);
	return (var_value);
}

char	*expand_quoted_variable(t_mshell *data, char *str, int *i, char *result)
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
}

char	*expand_double_quote(t_mshell *data, char *str)
{
	char	*result;
	int		len;
	int		i;
	int		result_len;

	i = 0;
	result_len = 0;
	len = ft_strlen(str);
	result = (char *)malloc(len + 1);
	while (i < len)
	{
		if (str[i] == '\"')
		{
			i++;
			result = expand_quoted_variable(data, str, &i, result);
		}
		else
			result[ft_strlen(result[result_len++])] = str[i++];
	}
	result[ft_strlen(result)] = '\0';
	return (result);
}

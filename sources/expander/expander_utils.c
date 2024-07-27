/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguandr <miguandr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 20:26:59 by miguandr          #+#    #+#             */
/*   Updated: 2024/07/27 21:07:13 by miguandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header_mig.h"

char	*remove_single_quote(char *str, t_mshell *data)
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
		handle_error(data, 0);
	while (i < len)
	{
		if (str[i] != '\'')
			result[j++] = str[i];
		i++;
	}
	return (result);
}

char	*single_quote_helper(char *str, t_mshell *data)
{
	char	*result;

	result = remove_single_quote(str, data);
	return (result);
}

char	*expand_double_quote_helper(t_mshell *data, char *str)
{
	char	*result;

	result = expand_double_quote(data, str);
	return (result);
}

char	*expand_variable_helper(t_mshell *data, char *str)
{
	char	*expanded_str;
	int		expanded_i;

	expanded_i = 0;
	expanded_str = expand_variable(data, str, &expanded_i);
	if (expanded_str)
		return (expanded_str);
	return (str);
}

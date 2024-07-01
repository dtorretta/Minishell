/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguandr <miguandr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:54:25 by miguandr          #+#    #+#             */
/*   Updated: 2024/07/01 00:48:14 by miguandr         ###   ########.fr       */
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
	var_value = get_variable_value(data, var_name);
	*index += ft_strlen(var_name) + 1;
	//free(var_name);
	//return var_value ? strdup(var_value) : NULL;
	return (var_value);
}

char	*handle_inside_quote(t_mshell *data, char *str, int *i, char *result)
{
	char	*var_value;
	int		result_len;

	result_len = ft_strlen(result);
	while (str[*i] && str[*i] != '\"')
	{
		if (str[*i] == '$')
		{
			var_value = expand_variable(data, str + *i, i);
			if (var_value)
			{
				ft_strcpy(result + result_len, var_value);
				result_len += ft_strlen(var_value);
				//free (var_value); //free or not? its maybe part of envp array?
			}
		}
		else
			result[result_len++] = str[(*i)++];
	}
	result[result_len] = '\0';
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
	result = (char *)malloc(len * 2);
	result[0] = '\0';
	while (i < len)
	{
		if (str[i] == '\"')
		{
			i++;
			result = handle_inside_quote(data, str, &i, result);
			if (str[i] == '\"')
				i++;
			result_len += ft_strlen(result);
		}
		else
		{
			result[result_len++] = str[i++];
		}
	}
	result[result_len] = '\0';
	return (result);
}

char	**expander(t_mshell *data, char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		if (ft_strchr(str[i], '\'') != NULL)
			str[i] = remove_single_quote(str[i]);
		else if (ft_strchr(str[i], '\"') != NULL)
			str[i] = expand_double_quote(data, str[i]);
		else
			str[i] = expand_variable(data, str[i], &i);
		i++;
	}
	return (str);
}


int main()
{
    // Sample data initialization (replace with your actual data initialization)
    t_mshell data;
    data.envp = (char **)malloc(4 * sizeof(char *));
    data.envp[0] = "VAR1=value1";
    data.envp[1] = "VAR2=value2";
    data.envp[2] = "HOME=/home/user";
    data.envp[3] = NULL;

    // Sample command strings with variables and quotes
    char **commands = (char **)malloc(11 * sizeof(char *));
    commands[0] = strdup("echo \"$HOME\"");
    commands[1] = strdup("echo 'Value is $VAR1'");
    commands[2] = strdup("echo \"Values: $VAR1 $VAR2\"");
    commands[3] = strdup("echo \"$NON_EXISTENT_VAR\"");
    commands[4] = strdup("echo NoQuotesHere");
    commands[5] = strdup("echo 'Only single quotes here'");
    commands[6] = strdup("echo \"Variable at the start: $VAR1\"");
    commands[7] = strdup("echo \"Variable in the middle: text $VAR1 text\"");
    commands[8] = strdup("echo \"Variable at the end: $VAR1\"");
    commands[9] = strdup("echo \"Multiple variables: $VAR1 $VAR2 $HOME\"");
    commands[10] = NULL;

    // Print original commands
    printf("Original Commands:\n");
    for (int i = 0; commands[i] != NULL; i++)
    {
        printf("%s\n", commands[i]);
    }
    printf("\n");

    // Expand variables and remove quotes
    commands = expander(&data, commands);

    // Print expanded commands
    printf("Expanded Commands:\n");
    for (int i = 0; commands[i] != NULL; i++)
    {
        printf("%s\n", commands[i]);
    }
    printf("\n");

    // Free allocated memory
    ft_free_array(commands);
    ft_free_array(data.envp);

    return 0;
}

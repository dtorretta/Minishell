/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguandr <miguandr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:54:25 by miguandr          #+#    #+#             */
/*   Updated: 2024/07/14 14:13:11 by miguandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header_mig.h"

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
				free (var_value);
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

	if (ft_strstr(str, "\"export\""))
		return (ft_strdup(str));
	i = 0;
	result_len = 0;
	len = ft_strlen(str);
	result = ft_calloc(MAX_EXP_SIZE, sizeof(char));
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
			result[result_len++] = str[i++];
	}
	return (result);
}

char	**expander(t_mshell *data, char **str)
{
	char	*temp;
	char	*expanded_str;
	int		i;
	int		expanded_i;

	i = 0;
	expanded_i = 0;
	while (str[i] != NULL)
	{
		if (ft_strchr(str[i], '\'') != NULL)
		{
			temp = str[i];
			str[i] = remove_single_quote(str[i]);
			free(temp);
		}
		else if (ft_strchr(str[i], '\"') != NULL)
		{
			temp = str[i];
			str[i] = expand_double_quote(data, str[i]);
			free(temp);
		}
		else if (ft_strchr(str[i], '$') != NULL)
		{
			expanded_str = expand_variable(data, str[i], &expanded_i);
			if (expanded_str)
			{
				free(str[i]);
				str[i] = expanded_str;
			}
		}
		i++;
	}
	return (str);
}

int main()
{
    // Sample data initialization (replace with your actual data initialization)
    t_mshell data;
    data.envp = (char **)malloc(5 * sizeof(char *));
    data.envp[0] = strdup("VAR1=value1");
    data.envp[1] = strdup("VAR2=value2");
    data.envp[2] = strdup("HOME=/home/user");
	data.envp[3] = strdup("export");
    data.envp[4] = NULL;

    // Sample command strings with variables and quotes
    char **commands = (char **)malloc(13 * sizeof(char *));
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
	commands[10] = strdup("echo \"export\"");
    commands[11] = NULL; // Make sure to terminate the array with NULL


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

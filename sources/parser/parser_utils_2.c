/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 18:40:59 by marvin            #+#    #+#             */
/*   Updated: 2024/07/14 18:40:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h" //modifica el nombre

//DEBERIMOS ARGEGAR UN CONTROL QUE NO PERMITA PONER COMADOS COMO LS?

//void * es un tipo de dato especial que se utiliza como un "tipo genérico" o "tipo de puntero genérico". Esto significa que puede apuntar a cualquier tipo de dato
// puede apuntar a cualquier cosa: números, caracteres, matrices, estructuras o incluso funciones
//Al utilizar void *, el array puede contener punteros a funciones de diferentes tipos de retorno.
//Cada elemento de la matriz commands_array es una combinación de una cadena (char*) y un puntero a una función.

//builtins_handler es una funcion que toma un argumento (char *str) y devuelve un puntero a una funcion que toma dos argumentos (t_mshell *minishell) & (t_parser *commands)
//es una función que, cuando se llama con un argumento char *str, devuelve un puntero a otra función.
//La función devuelta toma dos argumentos (ambos punteros a estructuras) y devuelve un entero

int	(*builtins_handler(char *str))(t_mshell *minishell, t_parser *commands)
{
	//el puntero minishel y commands no se usa ahora, si no que es necesario dentro de las funciones
	// ver si puedo pasar como parametro direecto el string
	static void *builtins_array [7][2] = {
		{"echo", mini_echo},
		{"cd", mini_cd},
		{"pwd", mini_pwd},
		{"export", mini_export},
		{"unset", mini_unset},
		{"env", mini_env},
		{"exit", mini_exit},
	};
	int	i;
	char	*expanded_str;

	i = 0;
	while (i < 7)
	{
		if (str && !ft_strncmp(builtins_array[i][0], str, ft_strlen(builtins_array[i][0])))
		{
			if (ft_strlen(str) != ft_strlen(builtins_array[i][0])) //ejemplo si tengo echoo.
				//add error y ver si contiene un return
				return(NULL);
			return (builtins_array[i][1]);
		}
		else
			i++;
	}
	return (NULL);
}

char	*expand_builtin(t_mshell *data, const char *str)
{
	char	*var_name;
	char	*var_value;
	char	*temp;
	char	*expanded_str;

	int i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			var_name = ft_substr(str, 0, i);
			i++;
			temp = strdup(str + i);
		}
		else
			i++;
	}
	var_value = get_variable_value(data, temp);
	expanded_str = ft_strjoin(var_name, var_value);
	free(var_name);
	free(var_value);
	if (expanded_str)
		return (expanded_str);
	else
		return (NULL);
}

char	**expander_builtins(t_mshell *data, char **str)
{
	char	*expanded_str;

	if (str[0])
	{
		if (ft_strchr(str[0], '$') != NULL)
		{
			expanded_str = expand_builtin(data, str[0]);
			if (expanded_str)
			{
				free(str[0]);
				str[0] = expanded_str;
			}
		}
	}
	return (str);
}

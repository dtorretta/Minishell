/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:24:04 by marvin            #+#    #+#             */
/*   Updated: 2024/07/02 23:24:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header_mig.h" //modifica el nombre

// unset: not enough arguments (revisar si comportamiento de solo unset en el campus)
// verificar si unset zz/ genera error de unset: not a valid identifier
// verificar si unset zzz= genera error de unset: not a valid identifier

//si solo tengo unset no pasa nada
//solo importa si hay coincidencia en el segundo argumento
//si hay mas o no hay coincidencia, no pasa nada
//export zzz=abc 
//unset zzz / "zzz" / 'zzz' (ok)
//unset zzz=abc / zzz= / zzzz / ZZZZ (NO)

static char *check_quote(char *str) //no borrar, es distinta a la otra
{
	int i;
	char *temp;
	char *substr;
	
	i = 0;
	while (str[i])
	{
		if(str[i] == '=')
		{
			substr = ft_substr(str, 0, i);
			temp = delete_quotes(substr); //si uno todo en la mism a linea funciona pero da memory leaks
			free(substr);
			return(temp);
		}
		i++;
	}
	temp = delete_quotes(str); //si no hay = de todos modos hay que darle valor a var name
	return(temp);
}

static char **newarray(char **array, char *str) //no borrar porque no es la misma que utils
{
	char **new_array;
	int i;
	int j;
	
	i = 0;
	while(array[i])
		i++;
	new_array = ft_calloc((i), sizeof(char*));
	if (!new_array)
		return (NULL); //cambiar
	i = 0;
	j = 0;
	while(array[i])
	{
		if(!ft_strncmp(array[i], str, ft_strlen(str)))
			i++;
		new_array[j++] = ft_strdup(array[i++]);
	}
	return(new_array);
}

int mini_unset (t_mshell *minishell, t_parser *commands)
{
	int i;
	char *env_var;
	char *unset_var;
	char **temp;
	
	i = -1;
	if(commands->str[1])
	{
		unset_var = check_quote(commands->str[1]);
		while(minishell->envp[++i])
		{
			env_var = check_quote(minishell->envp[i]); //separa de env pwd=lalal en solo pwd //revisar nombre funcion
			if(!ft_strncmp(env_var, unset_var, ft_strlen(unset_var))) //buscar en el array envp si se encuentra la variable definida con export
			{
				temp = newarray(minishell->envp, env_var);
				free_string_array(minishell->envp);
				minishell->envp = temp;
				if(!strncmp("PWD", unset_var, ft_strlen(unset_var)))
				{
				    free(minishell->pwd);
				    minishell->pwd = NULL;
                }
                if(!strncmp("OLDPWD", unset_var, ft_strlen(unset_var)))
				{
				    free(minishell->old_pwd);
				    minishell->old_pwd = NULL;
                }
                free(env_var);
				free(unset_var);
				return(EXIT_SUCCESS);
			}
			free(env_var);
		}
		free(unset_var);
		return(EXIT_SUCCESS); //si no hay coincidencia no pasa nada
	}
	return(EXIT_SUCCESS); // si solo esta unset, no pasa nada
}
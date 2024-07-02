/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:04:56 by marvin            #+#    #+#             */
/*   Updated: 2024/06/24 18:04:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h" //modifica el nombre

//si se ingresa solo export, sin ninguna otra variable, o si esa variable es "" (solo el caracter nulo) imprime el enviroment normal
//export VAR1
//si ejecuto expot solo, ahora voy a tener esa nueva variable
//export VAR1=1
//al ejecutar export --> VAR1="1"
//Esta variable se convierte en parte del entorno del shell y estará disponible para cualquier proceso hijo que se ejecute desde ese shell.
//export PWD=hola   --> va a actualizar el valor que tiene pwd

//revisar si el comando tiene =. si lo tiene:
//separar el comando por =
//buscar la primera parte en el array del envp
//si lo encuentra, actualizar el valor
//si no lo encuentra lo a;axde al final

char *delete_quotes (char *str) //BORRAR esta en utils
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

void print_array(char **array, int i) //BORRAR, ESTA EN UTILS
{
	while (array[i])
	{
		ft_putstr_fd(array[i], STDERR_FILENO);
		i++;
		if(array[i])
			write(2, " ", 1);        
	}
}

int	handle_error2(t_mshell *data, int error, char *str, char **array) //BORRAR. ESTA EN ERROR.C
{
	if(error == 1 || error == 2 || error == 4)
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		if(error == 1)
			print_array(array, 2); //que imprima del dos en adelante  
		else if(error == 2 || error == 4)
			ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	}
	else if (error == 3)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);                   
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": event not found", STDERR_FILENO); 
	}
	//reset_data(data);
	return(EXIT_FAILURE);
}

char **new_array(char **array, char *str) //BORRAR, ESTA EN UTILS
{
	char **new_array;
	int i;
	
	i = 0;
	while(array[i])
		i++;
	new_array = ft_calloc((i + 2), sizeof(char*));
	if (!new_array)
		return (NULL);
	i = 0;
	
	while(array[i])
	{
		new_array[i] = ft_strdup(array[i]);
		i++;
	}
	new_array[i] = str; //agrega la nueva variable como ultimo elemento
	return(new_array);
}

static int check_coincidence (t_mshell *minishell, int i, char *var_name, char *add_var)
{
	
	if(!ft_strncmp(minishell->envp[i], var_name, ft_strlen(var_name))) 
	{
		free(minishell->envp[i]);
		minishell->envp[i] = add_var;
		return(0);
	}
	return(1);
}

// Verifica si el carácter c es válido como parte de un identificador de variable en Bash
static bool check_valid_identifier(char c) 
{
	if ((c >= 'a' && c <= 'z') ||
		(c >= 'A' && c <= 'Z') ||
		(c >= '0' && c <= '9') ||
		c == '_' )
		return true;
	else 
		return false;
}

//elimina todos los quotes
//si encuentra =, almacena el nombre de la variable sin quotes en var_name
static char *check_quotes(char *str, char **var_name)
{
	int i;
	char *temp;
	//char *def;
	
	i = 0;
	temp = delete_quotes(str);
	while (str[i])
	{
		if(str[i] == '=')
		{
			i++;
			//temp = delete_quotes(ft_substr(str, 0, i)); //export varname & =
			*var_name = delete_quotes(ft_substr(str, 0, i)); //export varname & =
			//temp = delete_quotes(str);
			//*var_name = ft_strdup(temp); //revisar si esto sobrepasa esta funcion
			//def = delete_quotes(str + i); //lo que viene despues del ==
			//temp = ft_strjoin(temp, def); //varname & = & def
			return(temp);
		}
		else
			i++;
	}
	*var_name = delete_quotes(str); //si no hay = de todos modos hay que darle valor a var name
	//temp = delete_quotes(str);
	return(temp);
}

static int error_check (t_mshell *minishell, t_parser *commands)
{
	int i;
	
	i = 0;
	if (commands->str[2]) //si tengo mas de 3
		return(handle_error2(minishell, 1, NULL, commands->str));		
	else if (commands->str[1])
	{
		if (ft_isdigit(commands->str[1][0]) || commands->str[1][0] == '=')
			return(handle_error2(minishell, 2, commands->str[1], NULL));
		while (commands->str[1][i] != '=' && commands->str[1][i]) 
		{
			if (!check_valid_identifier(commands->str[1][i])) 
			{
				if (commands->str[1][i] == '!')
					return(handle_error2(minishell, 3, commands->str[1] + i, NULL));
				else
					return(handle_error2(minishell, 4, commands->str[1], NULL));
			}
			i++;
		}
	}
	return(EXIT_SUCCESS);
}

//str[0] --> export
//str[1] --> nombre de la variable (puede incluir la definicion)
//str[2] --> error ya que significa que el comando original tenia espacios
int mini_export (t_mshell *minishell, t_parser *commands)
{
	int i;
	char **temp;
	char *add_var;
	char *var_name;
	
	i = -1;
	if(error_check(minishell, commands)) //success 0 . failure 1
		return(EXIT_FAILURE);
	if(!commands->str[1] || commands->str[1][0] == '\0') //deberia imprimir algo mas que el enviroment???????
		mini_env(minishell, commands);
	else
	{
		add_var = check_quotes(commands->str[1], &var_name);//elimina los quotes de la variable (lo que esta antes de =)
		while(minishell->envp[++i])
		{
			if(check_coincidence(minishell, i, var_name, add_var) == 0)
				return(EXIT_SUCCESS);	
			// if(!ft_strncmp(minishell->envp[i], var_name, ft_strlen(var_name))) //buscar en el array envp si se encuentra la variable definida con export
			// {
			// 	coincidence(minishell, i, add_var);
			// 	return(EXIT_SUCCESS);
			// }
		}
		//free(temp); //si no lo encontro, entonces a;adirlo al final del array.  
		temp = new_array(minishell->envp, add_var);
		free(minishell->envp);
		minishell->envp = temp;
	}
	return(EXIT_SUCCESS);
}


//export zaq="\"hello\""
// --> declare -x zaq="\"hello\""



//unir lo de migue y lo mio
//volver a probar export


//export ZZZ="""abc"""
//export -> ZZZ="abc"              
//env -->  ZZZ=abc    //en mi codigo actual imprimiria ZZZ=abc ??

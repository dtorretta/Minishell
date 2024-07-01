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
	new_array[i] = str;
	return(new_array);
}

void coincidence (t_mshell *minishell, int i, char *add_var) //BORRAR, ESTA EN UTILS
{
	free(minishell->envp[i]);
	minishell->envp[i] = add_var;

}

static bool check_valid_identifier(char c) 
{
	// Verifica si el carácter c es válido como parte de un identificador de variable en Bash
	if ((c >= 'a' && c <= 'z') ||
		(c >= 'A' && c <= 'Z') ||
		(c >= '0' && c <= '9') ||
		c == '_' )
		return true;
	else 
		return false;
}

//si encuentra un = crea array
//array[0] --> nombre de la variable
//array[1] --> =
//array[2]--> nueva definificion
//array[3]--> null
//si recorre todo el while loop y no encontro nada, crea un array de 2 elementos donde el primero es todo el str y el 2do es NULL.
static char **check_command(char *str)
{
	char **array;
	int i;
	char *temp;
	
	i = 0;
	while (str[i])
	{
		if(str[i] == '=')
		{
			array = ft_calloc ((4), sizeof(char*));
			temp = ft_substr(str, 0, i); //esta bien el len?
			array[0] = temp;
			array[1] = ft_strdup("=");
			i++;
			array[2] = ft_strdup(str + i);
			return(array);
		}
		else
			i++;
	}
	array = ft_calloc ((2), sizeof(char*));
	if (!array)
		return (NULL); //ese necesario poner el return aca?
	array[0] = str; 
	return(array);
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

//echo """hello""" deberia borrar todos los ""
static char *var_name(char **array)
{
	char *str;
	
	if(!array[1])
		str = array[0];
	else
	{
		str = ft_strjoin(array[0], array [1]);
		str = ft_strjoin(str, "\"");
		str = ft_strjoin(str, array [2]);
		str = ft_strjoin(str, "\"");
	}
	return (str);
}

//str[0] --> export
//str[1] --> nombre de la variable (puede incluir la definicion)
//str[2] --> error ya que significa que el comando original tenia espacios
int mini_export (t_mshell *minishell, t_parser *commands)
{
	int i;
	char **temp;
	char *add_var;
	
	i = -1;
	if(error_check(minishell, commands)) //success 0 . failure 1
		return(EXIT_FAILURE);
	if(!commands->str[1] || commands->str[1][0] == '\0') //deberia imprimir algo mas que el enviroment???????
		mini_env(minishell, commands);
	else
	{
		temp = check_command(commands->str[1]);//va a ser un array de un solo elemento si no hay =   o de 3 si encuentra un = 
		add_var = var_name (temp);
		while(minishell->envp[++i])
		{
			if(!ft_strncmp(minishell->envp[i], temp[0], ft_strlen(temp[0]))) //buscar en el array envp si se encuentra la variable definida con export
				coincidence (minishell, i, add_var);
		}
		free(temp); //si no lo encontro, entonces a;adirlo al final del array.  
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


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

#include "../../includes/header_mig.h" //modifica el nombre

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

static int	check_coincidence(t_mshell *minishell, int i, char *var_name, char *add_var)
{

	if (!ft_strncmp(minishell->envp[i], var_name, ft_strlen(var_name)))
	{
		free(minishell->envp[i]);
		minishell->envp[i] = add_var;
		return (0);
	}
	return (1);
}

// Verifica si el carácter c es válido como parte de un identificador de variable en Bash
static bool	check_valid_identifier(char c)
{
	if ((c >= 'a' && c <= 'z') ||
		(c >= 'A' && c <= 'Z') ||
		(c >= '0' && c <= '9') ||
		c == '_' )
		return (true);
	else
		return (false);
}

//elimina todos los quotes
//si encuentra =, almacena el nombre de la variable sin quotes en var_name
static char	*check_quotes(char *str, char **var_name, t_mshell *minishell)
{
	int		i;
	char	*temp;
	//char *def;

	i = 0;
	temp = delete_quotes(str, minishell);
	while (str[i])
	{
		if (str[i] == '=')
		{
			//i++;
			//temp = delete_quotes(ft_substr(str, 0, i)); //export varname & =
			*var_name = delete_quotes(ft_substr(str, 0, i), minishell); //export varname & =
			//temp = delete_quotes(str);
			//*var_name = ft_strdup(temp); //revisar si esto sobrepasa esta funcion
			//def = delete_quotes(str + i); //lo que viene despues del ==
			//temp = ft_strjoin(temp, def); //varname & = & def
			return(temp);
		}
		else
			i++;
	}
	*var_name = delete_quotes(str, minishell); //si no hay = de todos modos hay que darle valor a var name
	//temp = delete_quotes(str);
	return(temp);
}

static int	error_check(t_mshell *minishell, t_parser *commands)
{
	int	i;

	i = 0;
	if (commands->str[1] && commands->str[2])
		return (handle_error2(minishell, 1, NULL, commands->str));
	else if (commands->str[1])
	{
		if (ft_isdigit(commands->str[1][0]) || commands->str[1][0] == '=')
			return (handle_error2(minishell, 2, commands->str[1], NULL));
		while (commands->str[1][i] != '=' && commands->str[1][i])
		{
			if (!check_valid_identifier(commands->str[1][i]))
			{
				if (commands->str[1][i] == '!')
					return (handle_error2(minishell, 3, commands->str[1] + i, NULL));
				else
					return (handle_error2(minishell, 4, commands->str[1], NULL));
			}
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

//str[0] --> export
//str[1] --> nombre de la variable (puede incluir la definicion)
//str[2] --> error ya que significa que el comando original tenia espacios
int	mini_export(t_mshell *minishell, t_parser *commands)
{
	int		i;
	char	**temp;
	char	*add_var;
	char	*var_name;

	i = -1;
	if (error_check(minishell, commands))
		return (EXIT_FAILURE);
	if (!commands->str[1] || commands->str[1][0] == '\0') //deberia imprimir algo mas que el enviroment???????
		mini_env(minishell, commands);
	else
	{
		add_var = check_quotes(commands->str[1], &var_name, minishell);//elimina los quotes de la variable (lo que esta antes de =)
		while(minishell->envp[++i])
		{
			if(check_coincidence(minishell, i, var_name, add_var) == 0)
				return(EXIT_SUCCESS);
		}
		temp = new_array(minishell->envp, add_var);
		free_string_array(minishell->envp);
		minishell->envp = temp;
		free(var_name);
	}
	return (EXIT_SUCCESS);
}

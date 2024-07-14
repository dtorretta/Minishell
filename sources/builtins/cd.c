/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 23:16:39 by marvin            #+#    #+#             */
/*   Updated: 2024/06/22 23:16:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h" //modifica el nombre

//cd sin ningún argumento cambia el directorio actual al directorio home 
//home esta en envp
//podemos usar la funcion chdir(ruta).
//chdir es una funcion int. retorna 0 si salio todo bien

// cd - cambia el directorio actual (PWD) al directorio anterior (OLDPWD)

//cuando cambiamos el directorio hay que actualizar el array donde tenemos pwd y oldpwd
//podemos usar la funcion getcwd --> pwd = getcwd(NULL, 0);
//o podemos volver a correr el while loop que buscaba pwd y oldpwd

//falta cd ..  ?



//reemplazo PWD y OLDPWD por sus nuevas rutas
static void	change_pwd(t_mshell *minishell)
{
	char *temp;
	
	temp = ft_strdup(minishell->pwd);
	free(minishell->old_pwd);
	minishell->old_pwd = temp;
	free(minishell->pwd);
	minishell->pwd = getcwd(NULL, 0);
}

//reescribe en el array envp PWD y OLDPWD.
static void	change_envp(t_mshell *minishell)
{
	int	i;
	char *temp;

	i = 0;
	while (minishell->envp[i])
	{
		if (ft_strncmp(minishell->envp[i], "PWD=", 4) == 0)
		{	
			temp = ft_strjoin("PWD=", minishell->pwd);
			free(minishell->envp[i]);
			minishell->envp[i] = temp;
		}	
		if (ft_strncmp(minishell->envp[i], "OLDPWD=", 7) == 0)
		{	
			temp = ft_strjoin("OLDPWD=", minishell->old_pwd);
			free(minishell->envp[i]);
			minishell->envp[i] = temp;
		}	
		i++;
	}
}

//a esta funcion solo entra si los argumentos son cd - o solo cd
static int	change_directory(char **env, char *str)
{
	int	i;
	char *new;
	char *temp;

	i = 0;
	temp = ft_strjoin(str, "=");
	while (env[i])
	{
		if (ft_strncmp(env[i], temp, ft_strlen(temp)) == 0)
			new = ft_strdup (env[i] + ft_strlen(temp));
		i++;
	}
	if(chdir(new) != 0)
	{
		ft_putstr_fd(str, 2);
		ft_putendl_fd(" not set", 2);
		free(temp);
		free(new);
		return (1);
	}
	free(temp);
	free(new);
	return (0);
}

//acepta 1 solo argumento que puede ser .. / - / nada / path
int mini_cd (t_mshell *minishell, t_parser *commands)
{  
	if(commands->str[1] && commands->str[2]) //si hay mas de 2 argumentos (si no agrego str[1] cuando solo tengo un argumento me da error de jump)
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	
	else if (!commands->str[1]) //si no hay argumentos
		change_directory(minishell->envp, "HOME");
		
	else if (!ft_strncmp(commands->str[1], "-", 1)) 
		change_directory(minishell->envp, "OLDPWD");
	
	else
	{
		if (chdir(commands->str[1]) != 0) //error en el cambio de directorio
		{
			ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
			ft_putstr_fd(commands->str[1], STDERR_FILENO);
			ft_putendl_fd(": No such file or directory", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
	}
	change_pwd(minishell);
	change_envp (minishell);
	return(0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:19:08 by miguandr          #+#    #+#             */
/*   Updated: 2024/08/02 20:05:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header_mig.h" //modifica el nombre


//en todas estas funciones no deberiamos agregar el minishell->exit_code???
int	handle_error(t_mshell *data, int error)
{
	(void)data;
	const char	*message;
	const char	*error_message[] = {
		"memory error: unable to allocate memory\n", //ok
		"syntax error: unable to find closing quotation\n", //ok
		"syntax error: command line can not begin/end with a token\n", //ok
		"syntax error: too many consecutive tokens\n", //ok
		"syntax error: wrong token handling\n", //ok
		"system error: failed to create child process\n", //ok
		"syntax error: not a valid builtin\n", //NOOOO
		"system error: failed to create pipe\n",  //ok
		"system error: error in fd\n",  //ok
	};

	message = error_message[error];
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(message, 1);
	data->exit_code = 2;
	reset_data(data);	
	return (EXIT_FAILURE);
}

int	handle_error2(t_mshell *data, int error, char *str, char **array)
{
	(void)data;
	if (error == 1 || error == 2 || error == 4)
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		if (error == 1)
			print_array(array, 2);
		else if (error == 2 || error == 4)
			ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	}
	else if (error == 3)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": event not found", STDERR_FILENO);
	}
	else if (error == 5)
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		return (2);
	}
	//reset_data(data); //reessetea todo y no me guarda el codigo de error
	return (EXIT_FAILURE);
}

int	handle_error3(t_mshell *data, int error, char *str)
{
	(void)data;

	if (error == 1)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
	}
	if (error == 2)
	{
		ft_putstr_fd("minishell: no such file or directory: ", STDERR_FILENO);
		ft_putendl_fd(str, STDERR_FILENO);
	}
	//reset_data(data); //no creo que sea necesario
	return(EXIT_FAILURE);
}

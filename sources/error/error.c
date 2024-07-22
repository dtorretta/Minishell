/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguandr <miguandr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:19:08 by miguandr          #+#    #+#             */
/*   Updated: 2024/07/22 20:56:36 by miguandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header_mig.h" //modifica el nombre


//en todas estas funciones no deberiamos agregar el minishell->exit_code???
int	handle_error(t_mshell *data, int error)
{
	(void)data;
	const char	*message;
	const char	*error_message[] = {
		"memory error: unable to allocate memory\n",
		"syntax error: unable to find closing quotation\n",
		"syntax error: command line can not begin/end with a token\n",
		"syntax error: too many consecutive tokens\n",
		"syntax error: wrong token handling\n",
		"system error: failed to create child process\n",
		"syntax error: not a valid builtin\n",
		"system error: failed to create pipe\n",
		"system error: error in fd\n",
	};

	message = error_message[error];
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(message, 1);
	//reset_data(data);
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
	}
	//reset_data(data);
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
	//reset_data(data);
	return(EXIT_FAILURE);
}

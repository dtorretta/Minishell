/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:19:08 by miguandr          #+#    #+#             */
/*   Updated: 2024/07/01 23:29:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header_mig.h"

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
	};

	message = error_message[error];
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(message, 1);
	//reset_data(data);
	return (EXIT_FAILURE);
}

int	handle_error2(t_mshell *data, int error, char *str, char **array)
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

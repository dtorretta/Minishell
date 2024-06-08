/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguandr <miguandr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:19:08 by miguandr          #+#    #+#             */
/*   Updated: 2024/06/08 20:48:46 by miguandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header_mig.h"

/*En esta funcion puedes agregar en error_message una nueva linea con
un nuevo mensaje de error. El programa cuenta intuitivamente la primera
linea como 0, luego 1, 2, 3 y asi*/
int	handle_error(t_mshell *data, int error)
{
	const char	*message;
	const char	*error_message[] = {
		"memory error: unable to allocate memory\n", //esto es error 0
		"syntax error: unable to find closing quotation\n", //esto es error 1
	};

	message = error_message[error];
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(message, 1);
	reset_data(data);
	return (EXIT_FAILURE);
}

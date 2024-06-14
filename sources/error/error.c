/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:19:08 by miguandr          #+#    #+#             */
/*   Updated: 2024/06/14 19:53:18 by marvin           ###   ########.fr       */
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

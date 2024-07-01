/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguandr <miguandr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 11:36:17 by miguandr          #+#    #+#             */
/*   Updated: 2024/06/30 13:49:40 by miguandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header_mig.h"

int	init_executor(t_mshell *data)
{
	signal(SIGQUIT, handle_ctrl_backslash);
	data->in_cmd = 1;
	if (data-> pipes == 0) // necesitamos una function que cuente los pipes, en el parser o en lexer?
		execute_single_cmd(data->simple_cmd, data); // ver si necesitamos crear simple_cmds o si cambiamos la logica
	else
	{
		data->pid = (int *)ft_calloc(data->pipes + 2, sizeof(int));
		if (!data->pid)
			return (handle_error(data, 1));
		execute_pipe_cmd(data);
	}
	data->in_cmd = 0;
	return (EXIT_SUCCESS);
}

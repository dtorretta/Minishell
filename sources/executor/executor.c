/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 11:36:17 by miguandr          #+#    #+#             */
/*   Updated: 2024/07/14 19:11:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header_mig.h"


//data->pipes + 1 = cfubre todos los procesos mientras que el +1 adicional es comúnmente utilizado para guardar un valor extra. Puede ser para propósitos de seguridad, alineación de memoria, o para almacenar un valor especial (como un PID extra o un valor sentinela).
//data->pid sera un array de enteros para los pid de cada proceso + 1 espacio extra
int	executor(t_mshell *data)
{
	signal(SIGQUIT, handle_ctrl_backslash);
	data->in_cmd = 1; //ver si necesitamos esto
	if (data-> pipes == 0) // YA LO AGREGUE EN EL PARSER
		execute_single_cmd(data->commands, data); // (migue) ver si necesitamos crear simple_cmds o si cambiamos la logica - (dani) tenemos la misma variable pero con el nombre commands en vez de simple_cmds
	else //(dani's part)
	{
		data->pid = (int *)ft_calloc(data->pipes + 2, sizeof(int));
		if (!data->pid)
			return (handle_error(data, 1));
		execute_pipe_cmd(data);
	}
	data->in_cmd = 0; //ver si necesitamos esto
	return (EXIT_SUCCESS);
}

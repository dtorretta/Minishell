/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 18:49:16 by marvin            #+#    #+#             */
/*   Updated: 2024/07/14 18:49:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header_mig.h"

//MODIFICAR
void	execute_pipe_cmd(t_mshell *minishell)
{
  	int		end[2];
	int		fd_in;

	fd_in = STDIN_FILENO;
	while (minishell->commands)
	{
		minishell->commands = call_expander(minishell, minishell->commands); //MIGUE
		if (minishell->commands->next)
			pipe(end);
		send_heredoc(minishell, minishell->commands); //MIGUE
		ft_fork(minishell, end, fd_in, minishell->commands);
		close(end[1]);
		if (minishell->commands->prev)
			close(fd_in);
		fd_in = check_fd_heredoc(minishell, end, minishell->commands);
		if (minishell->commands->next)
			minishell->commands = minishell->commands->next;
		else
			break ;
	}
	pipe_wait(minishell->pid, minishell->pipes);
	minishell->commands = ft_simple_cmdsfirst(minishell->commands);
	return (0);  
}



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

//Esta función juega un papel crucial al determinar de dónde debe leer el proceso hijo su entrada estándar (STDIN) antes de ejecutar un comando. Dependiendo de la configuración de tools->heredoc, decide entre leer de un heredoc o del extremo de lectura del pipe (end[0]).

// int	check_fd_heredoc(t_tools *tools, int end[2], t_simple_cmds *cmd)
// {
	
// }
void child_process(t_mshell *minishell, t_parser *commands, int fd[2], int fd_prev)
{
	if (commands->prev && dup2(fd_prev, STDIN_FILENO) < 0)
		return (EXIT_FAILURE); //CAMBIAR //ft_putstr_fd("Failed to create pipe\n", STDERR_FILENO);
	close(fd[0]);
	if (commands->next && dup2(fd[1], STDOUT_FILENO) < 0)
		return (EXIT_FAILURE); //CAMBIAR //ft_putstr_fd("Failed to create pipe\n", STDERR_FILENO);
	close(fd[1]);
	if(fd_prev)
		close(fd_prev);
	handle_cmd(minishell, commands); //TODO
	return (EXIT_SUCCESS); //necesario???
}

int ft_fork(t_mshell *minishell, t_parser *commands, int fd[2], int fd_prev)
{
	static int i;
	
	i = 0;
	if (minishell->reset == 1)
		i = 0;
	else
		minishell->pid[i] = fork();
	if (minishell->pid[i] < 0)
			return (EXIT_FAILURE); //CAMBIAR
	else if (minishell->pid[i] == 0)
		child_process(minishell, commands, fd, fd_prev);
	i++;
	return(EXIT_SUCCESS);
}
//cada vez que necesitas crear una comunicación entre dos procesos usando un pipe, necesitas:
//Declarar un array de dos enteros para almacenar los extremos de lectura y escritura del pipe.
//Usar la función pipe() para inicializar el pipe.

void	execute_pipe_cmd(t_mshell *minishell)
{
  	int		fd[2]; //fd
	int		fd_prev;
	
	int i = 0; //elementos del array de int para pid
	fd_prev = STDIN_FILENO;
	while (minishell->commands)
	{
		//minishell->commands = call_expander(minishell, minishell->commands); //MIGUE
		if (minishell->commands->next) //cada vez que tenga un next, va a crear un pipe para unir el current y el next
		{
			if(pipe(fd) == -1)
				return (EXIT_FAILURE); //CAMBIAR
		}
		//send_heredoc(minishell, minishell->commands); //MIGUE
		
		ft_fork(minishell, minishell->commands, fd, fd_prev); //cuando se crea un pipe voy a necesitar crear un childprocess
		
		minishell->pid[i] = fork(); //asigna el primer pid 
		if (minishell->pid[i] < 0)   
			return (EXIT_FAILURE); //CAMBIAR
		if (minishell->pid[i] == 0) //es el childprocess
		{
			close(fd[0]); //cierro la lectura
			//deberia agregarle los errores al dup??
			dup2(fd[1], STDOUT_FILENO); //Después de esta redirección, cualquier cosa que el proceso hijo escriba en la salida estándar será escrita en el pipe en lugar de la consola.
			execute(minishell, fd);
		}
		i++;
		
		
		
		close(fd[1]);
		if (minishell->commands->prev)
			close(fd_prev);
		fd_prev = check_fd_heredoc(minishell, fd, minishell->commands);
		if (minishell->commands->next)
			minishell->commands = minishell->commands->next;
		else
			break ;
	}
	pipe_wait(minishell->pid, minishell->pipes);
	minishell->commands = ft_simple_cmdsfirst(minishell->commands);
	return (0);  
}



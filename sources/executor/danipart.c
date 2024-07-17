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
#include <fcntl.h>  //a;adir al header

//return 0 ok / 1 error
int ft_redirections (t_parser *commands)
{



}

/*void handle_cmd(t_mshell *minishell, t_parser *commands)
{
	if(commands->num_redirections)
		minishell->exit_code = ft_redirections(commands);
	else
		minishell->exit_code = commands->builtins(minishell, commands); //ejecuto el builtin y almaceno el codigo de salida en la variable para su futura expansion
	exit (minishell->exit_code);
}*/



//Esta función juega un papel crucial al determinar de dónde debe leer el proceso hijo su entrada estándar (STDIN) antes de ejecutar un comando. 
//Dependiendo de la configuración de tools->heredoc, decide entre leer de un heredoc o del extremo de lectura del pipe (end[0]).
int	get_fd(t_mshell *minishell, int end[2], t_parser *commands)
{
	int fd;
	
	if(commands->heredoc)
	{
		close(end[0]);
		fd = open(commands->hd_file_name, O_RDONLY);
		if (fd < 0)
			return (EXIT_FAILURE); //CAMBIAR 
	}
	else
		fd = end[0];
	return(fd);
}

//redirecciono los files descriptor desde los cuales se van a leer / se va a almacenar la informacion en el caso que haya un comando previo o posterior respectivamente.
//Cuando cierras el extremo de escritura del pipe (end[1]) en el proceso hijo antes de ejecutar handle_cmd, no impides que los datos escritos por handle_cmd lleguen al siguiente comando.
void child_process(t_mshell *minishell, t_parser *commands, int fd[2], int fd_prev)
{
	if (commands->prev && dup2(fd_prev, STDIN_FILENO) < 0) //redirijo la lectura
		return (EXIT_FAILURE); //CAMBIAR //ft_putstr_fd("Failed to create pipe\n", STDERR_FILENO);
	close(fd[0]); //Cerrar extremo de lectura del pipe
	if (commands->next && dup2(fd[1], STDOUT_FILENO) < 0) //redirijo la escritura
		return (EXIT_FAILURE); //CAMBIAR //ft_putstr_fd("Failed to create pipe\n", STDERR_FILENO);
	close(fd[1]); //Cerrar extremo de escritura del pipe
	if(fd_prev)
		close(fd_prev);
	//ex  handle_cmd(minishell, commands);
	if(commands->num_redirections)
		minishell->exit_code = ft_redirections(commands); //TODO
	else
		minishell->exit_code = commands->builtins(minishell, commands); //ejecuto el builtin y almaceno el codigo de salida en la variable para su futura expansion
	exit (minishell->exit_code); //finaliza el proceso hijo
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

//Recorre todos los PIDs de los procesos hijos y espera a que terminen 
//Esto asegura que el proceso padre espere a que todos los procesos hijos terminen antes de continuar.
//el código de salida refleje el estado del último comando ejecutado.
//WIFEXITED(status): Verifica si el hijo terminó normalmente.
//WEXITSTATUS(status): Obtiene el código de salida del hijo.
void wait_childspid (t_mshell *minishell, int *array)
{
	int i;
	int status;
	
	i = 0;
	while(array[i])
	{
		waitpid(array[i], &status, 0);
		i++;	
	}
	if(WIFEXITED(status))
		minishell->exit_code = WEXITSTATUS(status);
	return(EXIT_SUCCESS);
}

//cada vez que necesitas crear una comunicación entre dos procesos usando un pipe, necesitas:
//Declarar un array de dos enteros para almacenar los extremos de lectura y escritura del pipe.
//Usar la función pipe() para inicializar el pipe.

void	execute_pipe_cmd(t_mshell *minishell)
{
  	int		fd[2];
	int		fd_prev;
	t_parser *temp_commands;
	
	int i = 0; //elementos del array de int para pid
	temp_commands = minishell->commands;
	fd_prev = STDIN_FILENO;
	while (temp_commands)
	{
		temp_commands = call_expander(minishell, temp_commands); //MIGUE
		if (temp_commands->next) //cada vez que tenga un next, va a crear un pipe para unir el current y el next
		{
			if(pipe(fd) == -1)
				return (EXIT_FAILURE); //CAMBIAR
		}
		send_heredoc(minishell, temp_commands); //MIGUE
		ft_fork(minishell, temp_commands, fd, fd_prev); //cuando se crea un pipe voy a necesitar crear un childprocess
		close(fd[1]);
		if (temp_commands->prev)
			close(fd_prev);
		fd_prev = get_fd(minishell, fd, temp_commands);
		temp_commands = temp_commands->next;
	}
	wait_childspid(minishell, minishell->pid); //minishell-> es un array de int con todos los PID. tengo que permite a un proceso padre esperar la terminación de un proceso hijo específico 
	return (EXIT_SUCCESS);  
}



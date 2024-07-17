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

//return 0 ok / 1 error
int ft_redirections (t_parser *commands)
{



}

//BORRAR
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
			return (handle_error(minishell, 7));
	}
	else
		fd = end[0];
	return(fd);
}

//Redirect the file descriptors from which file will be read / stored in 
// the case of a previous or subsequent command, respectively.
//Close(fd[0]) to close the read end of the pipe.
//Close(fd[1]) to close the write end of the pipe.
//If there is redirections, it executes ft_redirections, if not, executes
// the builtin and store the exit code in the variable for future expansion.
//Ends the child process and go back to the parent process
void child_process(t_mshell *minishell, t_parser *commands, int fd[2], int fd_prev)
{
	if (commands->prev && dup2(fd_prev, STDIN_FILENO) < 0)
		return (handle_error(minishell, 7));
	close(fd[0]);
	if (commands->next && dup2(fd[1], STDOUT_FILENO) < 0)
		return (handle_error(minishell, 7));
	close(fd[1]);
	if(fd_prev)
		close(fd_prev);
	//ex  handle_cmd(minishell, commands);
	if(commands->num_redirections)
		minishell->exit_code = ft_redirections(commands); //TODO !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	else if (commands->builtins)
		minishell->exit_code = commands->builtins(minishell, commands);
	else
		return (handle_error3(minishell, 1, commands->str[0])); //TEST por ejemplo ls
	exit (minishell->exit_code);
}

//Forks a child process to execute a command.
int ft_fork(t_mshell *minishell, t_parser *commands, int fd[2], int fd_prev)
{
	static int i;
	
	i = 0;
	if (minishell->reset == 1)
		i = 0;
	else
		minishell->pid[i] = fork();
	if (minishell->pid[i] < 0)
			return (handle_error(minishell, 5));
	else if (minishell->pid[i] == 0)
		child_process(minishell, commands, fd, fd_prev);
	i++;
	return(EXIT_SUCCESS);
}

//Recorre todos los PIDs de los procesos hijos y espera a que terminen 
//Esto asegura que el proceso padre espere a que todos los procesos hijos terminen antes de continuar.
//El código de salida refleja el estado del último comando ejecutado.
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

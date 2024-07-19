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

int ft_heredoc (t_parser *commands, t_mshell *minishell)
{

}

int ft_great (t_parser *commands, t_mshell *minishell)
{
	char *output;
	int file;
	
	output = commands->str;
	if(commands->redirections->token == GREAT)
		file = open(output, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if(commands->redirections->token == GREAT_GREAT)
		file = open(output, O_RDWR | O_CREAT | O_APPEND, 0644); 
	if(file < 0)
		return(handle_error(minishell, 8));
	if (dup2(file, STDOUT_FILENO) < 0)
	{	
		close(file);
		return (handle_error(minishell, 8));
	}
	commands->builtins(minishell, commands);	
	close(file);
	return(0);
}

int ft_less (t_parser *commands, t_mshell *minishell)
{
	char *input;
	int file;
			
	input = commands->str;
	file = open(input, O_RDONLY);
	if(file < 0)
		return(handle_error3(minishell, 2, file));
	if (dup2(file, STDIN_FILENO) < 0)
	{	
		close(file);
		return (handle_error(minishell, 8));
	}
	commands->builtins(minishell, commands);
	close(file);
	return(0);
}

//return 0 ok / 1 error
//abrimos el archivo output.txt en modo escritura. Si el archivo no existe, se crea. 
//O_TRUNC asegura que el archivo se vacía si ya existe.
//0644 es el modo de archivo que da permisos de lectura y escritura al propietario, y sólo de lectura al grupo y a otros.


//test.txt < wc -w (no deberia funcionar)
int ft_redirections (t_parser *commands, t_mshell *minishell)
{
	t_parser  *temp;
	temp = commands->redirections;
	
	while(temp)
	{
		if(commands->redirections->token == GREAT || commands->redirections->token == GREAT_GREAT)
			return(ft_great(commands, minishell));
		else if(commands->redirections->token == LESS)
			return(ft_less(commands, minishell));
		else if(commands->redirections->token == HERE_DOC)
			return(ft_heredoc(commands, minishell));
		else
			return(1);
		temp = temp->next;
	}
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
		minishell->exit_code = ft_redirections(commands, minishell); //TODO !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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

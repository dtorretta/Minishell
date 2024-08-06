/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguandr <miguandr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 11:36:17 by miguandr          #+#    #+#             */
/*   Updated: 2024/08/06 21:17:01 by miguandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header_mig.h" //modifica el nombre

/*static t_parser	*call_expander(t_mshell *data, t_parser *cmd)
{
	t_lexer	*start;

	expander(data, cmd->str);
	start = cmd->redirections;
	while (cmd->redirections)
	{
		if (cmd->redirections->token != HERE_DOC)
			cmd->redirections->str = expand_str(data, cmd->redirections->str);
		cmd->redirections = cmd->redirections->next;
	}
	cmd->redirections = start;
	return (cmd);
}*/

static void	check_heredoc(t_mshell *minishell, t_parser *commands)
{
	t_parser	*temp;

	temp = commands;
	while (temp && temp->redirections)
	{
		if (temp->redirections->token == HERE_DOC)
		{
			if (temp->hd_file_name)
				free(temp->hd_file_name);
			temp->hd_file_name = generate_name();
			minishell->exit_code = ft_heredoc(temp, minishell); //si se ejecuta bien exit_code tendra valor 0, esta bien que almacene codigos de exito?
			temp->heredoc = true;
			break ;
		}
		temp = temp->next;
	}
}

static int	is_main_process_builtin(int (*builtin)(t_mshell *, t_parser *)) //mejor poner todo junto
{
	return (builtin == mini_cd || builtin == mini_exit
		|| builtin == mini_export || builtin == mini_unset);
}

void	execute_single_cmd(t_parser *cmd, t_mshell *data)
{
	//t_parser	*expanded_cmds; no es necesario porque ya se expandio
	pid_t		pid;

	//expanded_cmds = call_expander(data, cmd);
	if (cmd && cmd->builtins && is_main_process_builtin(cmd->builtins)) //mejor poner todo aca junto
	{
		data->exit_code = cmd->builtins(data, cmd);
		return ;
	}
	check_heredoc(data, cmd);
	pid = fork();
	if (pid < 0)
		handle_error(data, 5);
	else if (pid == 0)
		execute_command(data, cmd);
		//execute_command(expanded_cmds, data);
	wait_childspid(data, (int[]){pid});
	//wait_for_child(data, pid);
}

//If there are multiple commands, creates a pipe to connect current and next.
//Every time communication between two processes is needed using a pipe:
// - Declare an array of two int to store the read and write ends of the pipe.
// - Use the pipe() function to initialize the pipe.
//If there is a PIPE token, spawns a child process.
int	execute_pipe_cmd(t_mshell *minishell)
{
	int			fd[2];
	int			fd_prev;
	t_parser	*temp_commands;
	//t_parser	*expanded_cmds; ahora: minishell->commands

	temp_commands = minishell->commands;
	fd_prev = STDIN_FILENO;
	while (temp_commands)
	{
		//expanded_cmds = call_expander(minishell, temp_commands);
		if (temp_commands->next)
		{
			if (pipe(fd) == -1)
				return (handle_error(minishell, 7));
		}
		//check_heredoc(minishell, temp_commands);
		ft_fork(minishell, temp_commands, fd, fd_prev);
		close(fd[1]);
		if (temp_commands->prev)
			close(fd_prev);
		fd_prev = get_fd(minishell, fd, temp_commands);
		temp_commands = temp_commands->next;
	}
	wait_childspid(minishell, minishell->pid);
	return (EXIT_SUCCESS);
}

//data->pipes + 1 = cfubre todos los procesos mientras que el +1 adicional es comúnmente utilizado para guardar un valor extra. Puede ser para propósitos de seguridad, alineación de memoria, o para almacenar un valor especial (como un PID extra o un valor sentinela).
//data->pid sera un array de enteros para los pid de cada proceso + 1 espacio extra
int	executor(t_mshell *data)
{
	signal(SIGINT, handle_ctrl_c_child);
	signal(SIGQUIT, handle_ctrl_backslash);
	data->in_cmd = 1; //ver si necesitamos esto
	if (data-> pipes == 0)
		execute_single_cmd(data->commands, data);
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

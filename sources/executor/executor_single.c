/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_single.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:45:01 by miguandr          #+#    #+#             */
/*   Updated: 2024/07/20 00:04:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header_mig.h"

// int	check_outfile(t_lexer *redirections)
// {
// 	int	fd;

// 	fd = check_append_outfile(redirections);
// 	if (fd < 0)
// 	{
// 		ft_putstr_fd("minishell/outfile: Error\n", STDERR_FILENO); //le falta lo de reset
// 		return (EXIT_FAILURE);
// 	}
// 	if (dup2(fd, STDOUT_FILENO) < 0)
// 	{
// 		ft_putstr_fd("minishell: pipe error\n", STDERR_FILENO); //le falta lo de reset
// 		close(fd);
// 		return (EXIT_FAILURE);
// 	}
// 	close (fd);
// 	return (EXIT_SUCCESS);
// }

// int	check_infile(char *file)
// {
// 	int	fd;

// 	fd = open(file, O_RDONLY);
// 	if (fd < 0)
// 	{
// 		ft_putstr_fd("Minishell/infile: No such file or directory\n", //le falta lo de reset
// 			STDERR_FILENO);
// 		return (EXIT_FAILURE);
// 	}
// 	if (dup2(fd, STDIN_FILENO) < 0)
// 	{
// 		ft_putstr_fd("Minishell: pipe error\n", STDERR_FILENO); //le falta lo de reset
// 		close(fd);
// 		return (EXIT_FAILURE);
// 	}
// 	close(fd);
// 	return (EXIT_SUCCESS);
// }

// int	check_redirections(t_parser *cmd)
// {
// 	t_lexer	*start;

// 	start = cmd->redirections;
// 	while (cmd->redirections)
// 	{
// 		// if (cmd->redirections->token == LESS
// 		// 	&& check_infile(cmd->redirections->str) == EXIT_FAILURE)
// 		// 	return (EXIT_FAILURE);
// 		// if ((cmd->redirections->token == GREAT
// 		// 		|| cmd->redirections->token == GREAT_GREAT)
// 		// 	&& check_outfile(cmd->redirections) == EXIT_FAILURE)
// 		// 	return (EXIT_FAILURE);
// 		if (cmd->redirections->token == HERE_DOC
// 			&& check_infile(cmd->hd_file_name) == EXIT_FAILURE)
// 			return (EXIT_FAILURE);
// 		cmd->redirections = cmd->redirections->next;
// 	}
// 	cmd->redirections = start;
// 	return (EXIT_SUCCESS);
// }



//la idea no era usar exit_status y usar la variable definida dentro de la estructura minishell??
/*void	execute_command(t_parser *cmd, t_mshell *data)
{
	int	exit_status;

	exit_status = 0;
	if (check_redirections(cmd) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	// if (cmd->builtins)
	// {
	// 	exit_status = cmd->builtins(data, cmd);
	// 	exit(exit_status);
	// }
	else
	{
		exit_status = find_command(cmd, data); //ver si es necesario
		exit(exit_status);
	}
} */

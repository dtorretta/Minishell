/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miguepart.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguandr <miguandr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 20:49:13 by miguandr          #+#    #+#             */
/*   Updated: 2024/07/17 19:51:29 by miguandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header_mig.h"

t_parser	*call_expander(t_mshell *data, t_parser *cmd)
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
}

void	execute_single_cmd(t_parser *cmd, t_mshell *data)
{
	t_parser	*expanded_cmds;
	pid_t		pid;

	expanded_cmds = call_expander(data, cmd);
	if (cmd->builtins && is_main_process_builtin(cmd->builtins))
	{
		data->exit_code = cmd->builtins(data, cmd);
		return ;
	}
	//send_heredoc(data, cmd);
	pid = fork();
	if (pid < 0)
		handle_error(data, 5);
	else if (pid == 0)
		execute_command(expanded_cmds, data);
	wait_for_child(data, pid);
}

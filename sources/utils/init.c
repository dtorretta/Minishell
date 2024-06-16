/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguandr <miguandr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 21:10:52 by miguandr          #+#    #+#             */
/*   Updated: 2024/06/16 21:20:09 by miguandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header_mig.h"

int	init_data(t_mshell *data)
{
	data->simple_cmds = NULL;
	data->lexer_list = NULL;
	data->reset = false;
	data->pid = NULL;
	data->heredoc = false;
	//g_global.stop_heredoc = 0;
	//g_global.in_cmd = 0;
	//g_global.in_heredoc = 0;
	handle_envp(&data);
	init_signals();
	return (1);
}

int	reset_data(t_mshell *data)
{
	ft_simple_cmds_clear(&data->simple_cmds); // MAKE
	free(data->args);
	if (data->pid)
		free(data->pid);
	ft_free_array(data->paths);
	init_data(data);
	data->reset = true;
	lexer(data);
	return (1);
}

void	builtins_clear(t_simple_cmds **list)
{
	t_simple_cmds	*current;
	t_simple_cmds	*next;
	t_lexer			*redirection_temp;

	if (!list || !*list)
		return ;
	current = *list;
	while (current)
	{
		next = current->next;
		redirection_temp = current->redirections;
		ft_lexer_clear(&redirection_temp);
		current->redirections = redirection_temp;
		if (current->str)
			ft_free_array(current->str);
		if (current->hd_file_name)
			free(current->hd_file_name);
		free(current);
		current = next;
	}
	*list = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguandr <miguandr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 21:10:52 by miguandr          #+#    #+#             */
/*   Updated: 2024/07/22 21:10:13 by miguandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header_mig.h"

int	init_data(t_mshell *data)
{
	data->commands = NULL;
	data->lexer_list = NULL;
	data->reset = false;
	data->pid = NULL;
	data->pipes = 0;
	data->exit_code = 0;
	//g_global.stop_heredoc = 0;
	//g_global.in_cmd = 0;
	//g_global.in_heredoc = 0;
	data->in_cmd = 0;
	handle_envp(data);
	init_signals();
	return (1);
}

void	ft_commands_clear(t_parser **lst)
{
	t_parser	*tmp;
	t_lexer			*redirections_tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		redirections_tmp = (*lst)->redirections;
		free_lexer_list(redirections_tmp);
		if ((*lst)->str)
			ft_free_array((*lst)->str);
		if ((*lst)->hd_file_name)
			free((*lst)->hd_file_name);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

int	reset_data(t_mshell *data)
{
	ft_commands_clear(&data->commands); // MAKE
	free(data->args);
	if (data->pid)
		free(data->pid);
	ft_free_array(data->paths);

	init_data(data);
	data->reset = true;
	minishell(data);
	return (1);
}

/*BUILTIN CLEAR... Ver en donde recolocar*/
/*void	builtins_clear(t_parser **list)
{
	t_parser	*current;
	t_parser	*next;
	t_lexer		*redirection_temp;

	if (!list || !*list)
		return ;
	current = *list;
	while (current)
	{
		next = current->next;
		redirection_temp = current->redirections;
		lexer_delete_all(&redirection_temp);
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
*/

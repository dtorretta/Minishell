/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguandr <miguandr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:43:09 by miguandr          #+#    #+#             */
/*   Updated: 2024/06/08 20:46:18 by miguandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header_mig.h"

int	lexer(t_mshell *data)
{
	const char	*prompt;
	char		*user_input;
	char		*trimmed_input;

	prompt = "minishell> ";
	user_input = readline(prompt);
	trimmed_input = ft_strtrim(user_input, " ");
	free(user_input);
	data->args = trimmed_input;
	if (!data->args)
	{
		ft_putendl_fd("exit", 1);
		exit(EXIT_SUCCESS);
	}
	if (data->args == '\0')
		return (reset_data(data)); // DESARROLLAR reset_data
	add_history(data->args);
	if (!count_quotes(data->args))
		return (handle_error(data, 1));
	if (!read_token(data->args)) // DESARROLLAR read_token
		return (handle_error(data, 0));
	return (1);
}

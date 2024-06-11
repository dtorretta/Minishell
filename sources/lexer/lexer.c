/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguandr <miguandr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:43:09 by miguandr          #+#    #+#             */
/*   Updated: 2024/06/11 15:32:14 by miguandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header_mig.h"

int	tokenizer(t_mshell *data)
{
	int	i;
	int	handled;

	i = 0;
	while (data->args[i])
	{
		i = skip_space(data->args, i);
		handled = 0;
		if (check_token(data->args[i]))
			handled = handle_token(data->args, i, &data->lexer_list);
		else
			handled = handle_word(data->args, i, &data->lexer_list);
		if (handled < 0)
			return (0);
		i += handled;
	}
	return (1);
}

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
	//if (*data->args == '\0')
	//	return (reset_data(data)); // MAKE reset_data
	add_history(data->args);
	if (!count_quotes(data->args))
		return (handle_error(data, 1));
	if (!tokenizer(data))
		return (handle_error(data, 0));
	lexer_error_check(data->lexer_list, data);
	return (1);
}

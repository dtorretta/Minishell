/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguandr <miguandr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:59:12 by miguandr          #+#    #+#             */
/*   Updated: 2024/06/11 16:55:21 by miguandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header_mig.h"

t_tokens	check_token(int c)
{
	if (c == '|')
		return (PIPE);
	else if (c == '>')
		return (GREAT);
	else if (c == '<')
		return (LESS);
	else
		return (0);
}

static int	process_double(char *str, int i, t_tokens token, t_lexer **list)
{
	t_tokens	double_token;

	if (token == GREAT && check_token(str[i + 1]) == GREAT)
		double_token = GREAT_GREAT;
	else if (token == LESS && check_token(str[i + 1]) == LESS)
		double_token = LESS_LESS;
	else
		return (0);
	if (!add_node(NULL, double_token, list))
		return (-1);
	return (2);
}

static int	process_single(t_tokens token, t_lexer **list)
{
	if (!add_node(NULL, token, list))
		return (-1);
	return (1);
}

int	handle_token(char *str, int i, t_lexer **lexer_list)
{
	t_tokens	token;
	int			result;

	token = check_token(str[i]);
	if (token == GREAT || token == LESS)
	{
		result = process_double(str, i, token, lexer_list);
		if (result != 0)
			return (result);
	}
	if (token)
		return (process_single(token, lexer_list));
	return (0);
}

int	handle_word(char *str, int start, t_lexer **lexer_list)
{
	int	len;

	len = 0;
	while (str[start + len] && (!check_token(str[start + len])
			&& !ft_iswhitespace(str[start + len])))
	{
		len += skip_quotes(str, start + len, 34);
		len += skip_quotes(str, start + len, 39);
		if (str[start + len] && (!check_token(str[start + len])
				&& !ft_iswhitespace(str[start + len])))
			len++;
	}
	if (!add_node(ft_substr(str, start, len), WORD, lexer_list))
		return (-1);
	return (len);
}

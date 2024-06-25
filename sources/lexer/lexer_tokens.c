/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguandr <miguandr@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:59:12 by miguandr          #+#    #+#             */
/*   Updated: 2024/06/25 22:07:55 by miguandr         ###   ########.fr       */
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
		double_token = HERE_DOC;
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
	char	*cleaned_word;
	int		i;
	int		len;

	len = 0;
	i = 0;
	cleaned_word = (char *)malloc(ft_strlen(str) + 1);
	if (!cleaned_word)
		return (-1);
	while (str[start + len] && (!check_token(str[start + len])
			&& !ft_iswhitespace(str[start + len])))
	{
		if (str[start + len] == '\"' || str[start + len] == '\'')
			len += copy_quoted_content(str, start + len, cleaned_word, &i);
		else
			cleaned_word[i++] = str[start + len++];
	}
	cleaned_word[i] = '\0';
	if (!add_node(ft_strdup(cleaned_word), WORD, lexer_list))
	{
		free(cleaned_word);
		return (-1);
	}
	free(cleaned_word);
	return (len);
}
